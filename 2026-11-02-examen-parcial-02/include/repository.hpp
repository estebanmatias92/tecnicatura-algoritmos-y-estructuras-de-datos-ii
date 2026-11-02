#ifndef PARTIAL02_REPOSITORY_HPP
#define PARTIAL02_REPOSITORY_HPP

#include <optional>
#include <vector>

namespace partial02 {

/// Contrato de almacenamiento de solo lectura por clave.
///
/// Los métodos de consulta retornan punteros estables al almacenamiento interno
/// (no copias), así que los llamadores pueden guardar punteros a entidades
/// sin que caduquen. Esto es necesario porque PurchaseOrder referencia
/// Article y Supplier mediante punteros no propietarios (ADR-0002).
template <class T, class K>
class Repository {
public:
    virtual ~Repository() = default;

    /// Busca una entidad por su clave. Retorna nullptr si no existe.
    virtual const T* find(const K& key) const = 0;

    /// Retorna punteros a todas las entidades.
    virtual std::vector<const T*> all() const = 0;

    /// Agrega una entidad (copia al almacenamiento interno).
    /// Lanza si la clave ya existe.
    virtual void add(const T& entity) = 0;
};

/// Contrato de almacenamiento mutable: agrega update y remove.
/// Solo las entidades con CRUD completo (Supplier) implementan esta interfaz
/// (ISP).
template <class T, class K>
class MutableRepository : public Repository<T, K> {
public:
    ~MutableRepository() override = default;

    virtual void update(const T& entity) = 0;
    virtual void remove(const K& key) = 0;
};

}  // namespace partial02

#endif  // PARTIAL02_REPOSITORY_HPP
