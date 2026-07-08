# Consigna 3.2 - Capa de base de datos SQLite
# Consigna 3.3 - Tabla usuarios para login

import sqlite3
import os

DB_PATH = os.path.join(os.path.dirname(__file__), "..", "pedidos.db")


def get_connection():
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn


def init_db():
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS pedidos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            cliente TEXT NOT NULL,
            direccion TEXT NOT NULL,
            inconveniente TEXT,
            tecnico TEXT,
            visita TEXT
        )
    """)
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS usuarios (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            usuario TEXT UNIQUE NOT NULL,
            clave TEXT NOT NULL
        )
    """)
    conn.commit()
    conn.close()


def seed_admin():
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute("SELECT COUNT(*) FROM usuarios")
    if cursor.fetchone()[0] == 0:
        cursor.execute(
            "INSERT INTO usuarios (usuario, clave) VALUES (?, ?)",
            ("admin", "admin123"),
        )
        conn.commit()
    conn.close()


def validate_login(usuario, clave):
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute(
        "SELECT * FROM usuarios WHERE usuario = ? AND clave = ?",
        (usuario, clave),
    )
    result = cursor.fetchone()
    conn.close()
    return result is not None


def create_pedido(cliente, direccion, inconveniente, tecnico, visita):
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute(
        """INSERT INTO pedidos (cliente, direccion, inconveniente, tecnico, visita)
        VALUES (?, ?, ?, ?, ?)""",
        (cliente, direccion, inconveniente, tecnico, visita),
    )
    conn.commit()
    pedido_id = cursor.lastrowid
    conn.close()
    return pedido_id


def get_pedidos():
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM pedidos ORDER BY id DESC")
    rows = cursor.fetchall()
    conn.close()
    return [dict(row) for row in rows]


def update_pedido(pedido_id, cliente, direccion, inconveniente, tecnico, visita):
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute(
        """UPDATE pedidos SET cliente = ?, direccion = ?, inconveniente = ?,
        tecnico = ?, visita = ? WHERE id = ?""",
        (cliente, direccion, inconveniente, tecnico, visita, pedido_id),
    )
    conn.commit()
    conn.close()


def delete_pedido(pedido_id):
    conn = get_connection()
    cursor = conn.cursor()
    cursor.execute("DELETE FROM pedidos WHERE id = ?", (pedido_id,))
    conn.commit()
    conn.close()
