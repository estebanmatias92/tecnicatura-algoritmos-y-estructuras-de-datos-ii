import unittest
from src.ejercicios.seccion_10_testing.funciones import calcula_media


class TestCalculaMedia(unittest.TestCase):
    def setUp(self):
        print("  Entra setUp")

    def tearDown(self):
        print("  Entra tearDown")

    def test_1(self):
        resultado = calcula_media([10, 10, 10])
        self.assertEqual(resultado, 10)

    def test_2(self):
        resultado = calcula_media([5, 3, 4])
        self.assertEqual(resultado, 4)


class TestEjemplos(unittest.TestCase):
    def setUp(self):
        print("  Entra setUp (TestEjemplos)")

    def tearDown(self):
        print("  Entra tearDown (TestEjemplos)")

    def test_1(self):
        print("  Test: test_1")

    def test_2(self):
        print("  Test: test_2")


if __name__ == "__main__":
    unittest.main()
