# Glosario de Dominio — Python OOP

## Términos

| Término | Definición |
|---------|------------|
| **Clase** | Plantilla o molde para crear objetos. Define atributos y métodos comunes. |
| **Objeto / Instancia** | Entidad concreta creada a partir de una clase, con estado propio (atributos de instancia). |
| **Atributo de clase** | Variable compartida por todas las instancias de una clase. Se define directamente en el cuerpo de la clase. |
| **Atributo de instancia** | Variable perteneciente a una instancia específica. Se define normalmente en `__init__`. |
| **Constructor (`__init__`)** | Método especial que se ejecuta al crear una instancia, usado para inicializar atributos. |
| **Decorador** | Función que toma otra función y extiende su comportamiento sin modificarla explícitamente. Se aplica con `@`. |
| **Método de instancia** | Método que recibe `self` como primer parámetro y opera sobre una instancia concreta. |
| **Método de clase (`@classmethod`)** | Método que recibe `cls` como primer parámetro y opera sobre la clase en sí. |
| **Método estático (`@staticmethod`)** | Método que no recibe ni `self` ni `cls`; funciona como una función dentro de la clase. |
| **Herencia** | Mecanismo por el cual una clase (subclase) deriva de otra (superclase), heredando sus atributos y métodos. |
| **`super()`** | Función que permite llamar a métodos de la clase padre desde la subclase. |
| **Herencia múltiple** | Capacidad de una clase de heredar de más de una clase base. |
| **MRO (Method Resolution Order)** | Orden en que Python busca métodos en la jerarquía de herencia múltiple (algoritmo C3 linearization). |
| **`__bases__`** | Atributo de clase que devuelve una tupla con las clases base directas. |
| **`__subclasses__()`** | Método de clase que devuelve una lista de las subclases directas. |
| **`@property`** | Decorador que permite definir un método que se accede como si fuera un atributo (getter). |
| **`@<atributo>.setter`** | Decorador que permite definir un setter para una propiedad. |
| **Encapsulamiento** | Principio POO que restringe el acceso directo a los atributos de un objeto, exponiendo solo una interfaz controlada. |
| **`_variable`** | Convención en Python para indicar un atributo "protegido" (uso interno, no público). |
| **`__variable`** | Name mangling en Python: Python renombra internamente el atributo para evitar colisiones en herencia. |
| **Abstracción** | Principio POO que oculta la complejidad interna exponiendo solo una interfaz simple. |
| **Acoplamiento (coupling)** | Grado de dependencia entre módulos/clases. Bajo acoplamiento es deseable. |
| **Cohesión** | Grado en que los elementos de un módulo/clase están relacionados entre sí. Alta cohesión es deseable. |
| **Polimorfismo** | Capacidad de objetos de distintas clases de responder al mismo mensaje (método) de forma específica. |
| **Clase abstracta (ABC)** | Clase que no puede instanciarse directamente; define una interfaz que las subclases deben implementar. |
| **`@abstractmethod`** | Decorador que marca un método como abstracto, obligando a las subclases a implementarlo. |
| **Interfaz** | Contrato que define qué métodos debe exponer una clase, sin especificar cómo se implementan. |
| **Interfaz informal** | Interfaz basada en convención y Duck Typing: no hay verificación en tiempo de compilación. |
| **Interfaz formal** | Interfaz definida mediante ABC (Abstract Base Class) con verificación en tiempo de ejecución. |
| **Clase virtual** | Clase que se registra como subclase de una ABC sin heredar de ella (vía `register()`). |
| **Duck Typing** | "Si camina como pato y suena como pato, entonces es un pato": Python se basa en la presencia de métodos, no en el tipo declarado. |
