-- Esquema inicial de Productos de Goma (Parcial 02)
-- Aplicado automáticamente al crear el volumen de MariaDB.

CREATE TABLE IF NOT EXISTS suppliers (
    cuit CHAR(11) NOT NULL,
    business_name VARCHAR(120) NOT NULL,
    PRIMARY KEY (cuit)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- BR-004: CUIT es la clave, 11 dígitos, único.
-- Se guarda sin guiones, igual que se ingresa.

CREATE TABLE IF NOT EXISTS articles (
    code VARCHAR(20) NOT NULL,
    description VARCHAR(200) NOT NULL DEFAULT '',
    unit_price_cents BIGINT NOT NULL,
    PRIMARY KEY (code)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- BR-002: código único y no vacío.
-- BR-003: precio en centavos (BIGINT), nunca DOUBLE.
-- CHECK (unit_price_cents > 0) se agrega como constraint con nombre.

ALTER TABLE articles
    ADD CONSTRAINT chk_articles_price_positive
    CHECK (unit_price_cents > 0);

CREATE TABLE IF NOT EXISTS purchase_orders (
    number INT UNSIGNED NOT NULL,
    supplier_cuit CHAR(11) NOT NULL,
    created_at DATE NOT NULL,
    expected_delivery DATE NOT NULL,
    PRIMARY KEY (number),
    CONSTRAINT fk_purchase_orders_supplier
        FOREIGN KEY (supplier_cuit) REFERENCES suppliers(cuit)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- BR-010: el número lo asigna la aplicación antes del insert
-- (OrderNumberSequence), no AUTO_INCREMENT. El seed inserta 1..3.
-- BR-011: CHECK (expected_delivery >= created_at).

ALTER TABLE purchase_orders
    ADD CONSTRAINT chk_orders_delivery_not_before_creation
    CHECK (expected_delivery >= created_at);

CREATE TABLE IF NOT EXISTS purchase_order_items (
    order_number INT UNSIGNED NOT NULL,
    article_code VARCHAR(20) NOT NULL,
    quantity INT UNSIGNED NOT NULL,
    position SMALLINT UNSIGNED NOT NULL,
    PRIMARY KEY (order_number, article_code),
    CONSTRAINT fk_items_order
        FOREIGN KEY (order_number) REFERENCES purchase_orders(number),
    CONSTRAINT fk_items_article
        FOREIGN KEY (article_code) REFERENCES articles(code)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- BR-008: clave primaria compuesta impide cargar el mismo artículo
-- dos veces en un pedido.
-- BR-001: CHECK (quantity > 0).
-- position preserva el orden de carga (RN-007).

ALTER TABLE purchase_order_items
    ADD CONSTRAINT chk_items_quantity_positive
    CHECK (quantity > 0);

-- Nota: solo suppliers se modifica y se elimina desde la aplicación.
-- purchase_orders es append-only y articles se da de alta en runtime.
-- El seed es fuente inicial de artículos y pedidos de demostración.
