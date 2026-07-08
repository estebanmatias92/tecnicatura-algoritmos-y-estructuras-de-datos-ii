# Glosario de Dominio — Abstract Factory (Mueblería)

| Término | Definición | Contexto |
|---|---|---|
| **Patrón Creacional** | Patrón de diseño que abstrae el proceso de creación de objetos, ocultando la lógica de instanciación. | Marco Teórico — Pregunta 4 |
| **Abstract Factory** | Patrón creacional que permite producir familias de objetos relacionados sin especificar sus clases concretas. | Marco Práctico — Consigna 1 |
| **Producto Abstracto** | Interfaz que declara las operaciones comunes para un tipo de producto dentro de una familia. | Ej: `Chair`, `Sofa`, `CoffeeTable` |
| **Producto Concreto** | Implementación específica de un producto abstracto para una variante determinada. | Ej: `ModernChair`, `VictorianSofa` |
| **Fábrica Abstracta** | Interfaz que declara métodos de creación para cada tipo de producto de la familia. | `MuebleriaFactory` |
| **Fábrica Concreta** | Implementa la fábrica abstracta para una variante específica, creando productos de esa familia. | `ModernFactory`, `VictorianFactory`, `ArtDecoFactory` |
| **Familia de Productos** | Conjunto de productos relacionados que deben usarse juntos (misma variante). | `Chair + Sofa + CoffeeTable` en estilo Modern, Victorian o ArtDeco |
| **Variante** | Estilo o línea de diseño que define una familia completa de productos. | Modern, Victorian, ArtDeco |
| **Cliente** | Código que utiliza la fábrica abstracta para crear productos, sin conocer las clases concretas. | `main.cpp` / `MuebleriaApp` |
