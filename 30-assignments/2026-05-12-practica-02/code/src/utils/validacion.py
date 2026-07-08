class Validacion:

    @staticmethod
    def es_positivo(valor: int) -> bool:
        return valor > 0

    @staticmethod
    def esta_en_rango(valor: int, min_val: int, max_val: int) -> bool:
        return min_val <= valor <= max_val
