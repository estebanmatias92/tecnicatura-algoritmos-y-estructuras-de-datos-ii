import inspect
import sys


class Registry:
    _ejercicios: dict[int, dict[int, dict]] = {}

    @classmethod
    def registrar(cls, seccion: int, numero: int, titulo: str):
        def decorador(func):
            if seccion not in cls._ejercicios:
                cls._ejercicios[seccion] = {}
            cls._ejercicios[seccion][numero] = {
                "func": func,
                "titulo": titulo,
                "seccion": seccion,
                "numero": numero,
            }
            return func
        return decorador

    @classmethod
    def obtener_por_seccion(cls, seccion: int) -> list[dict]:
        return list(cls._ejercicios.get(seccion, {}).values())

    @classmethod
    def secciones_disponibles(cls) -> dict[int, list[int]]:
        return {s: sorted(e.keys()) for s, e in cls._ejercicios.items()}

    @classmethod
    def ejercicios_totales(cls) -> dict:
        return cls._ejercicios

    @classmethod
    def importar_modulos_ejercicios(cls):
        modulos = [
            "src.ejercicios.seccion_01_entorno",
            "src.ejercicios.seccion_02_venv",
            "src.ejercicios.seccion_03_colecciones",
            "src.ejercicios.seccion_04_bucles",
            "src.ejercicios.seccion_05_funciones",
            "src.ejercicios.seccion_06_funcional",
            "src.ejercicios.seccion_07_excepciones",
            "src.ejercicios.seccion_08_archivos",
        ]
        for mod in modulos:
            __import__(mod, fromlist=[""])
