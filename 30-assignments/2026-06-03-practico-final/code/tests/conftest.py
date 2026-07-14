import sqlite3

import pytest

from consultorio import Consultorio


@pytest.fixture
def consultorio():
    conn = sqlite3.connect(":memory:")
    c = Consultorio(conn)
    c.inicializar()
    yield c
    conn.close()
