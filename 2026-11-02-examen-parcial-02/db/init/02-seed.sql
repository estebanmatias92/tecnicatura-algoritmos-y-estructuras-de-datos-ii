-- Seed de Productos de Goma (Parcial 02)
-- Datos de demostración para artículos y pedidos.
-- Los números de pedido son explícitos (1, 2, 3); el siguiente pedido nuevo
-- recibe el 4 (BR-010: la aplicación asigna MAX(number)+1 antes del insert).

-- ===== Proveedores =====
INSERT INTO suppliers (cuit, business_name) VALUES
    ('20234567891', 'Insumos Andinos S.R.L.'),
    ('27334455669', 'Química del Plata S.A.'),
    ('30712345678', 'Cauchos del Sur S.A.');

-- ===== Artículos (catálogo) =====
INSERT INTO articles (code, description, unit_price_cents) VALUES
    ('CAU-001', 'Caucho natural', 150000),
    ('AZU-002', 'Azufre', 80000),
    ('NEG-003', 'Negro de humo', 220000),
    ('ACE-004', 'Aceite de proceso', 95000);

-- ===== Pedidos (append-only) =====
-- Pedido 1: Cauchos del Sur, creado 2026-10-20, entrega 2026-11-05
INSERT INTO purchase_orders (number, supplier_cuit, created_at, expected_delivery) VALUES
    (1, '30712345678', '2026-10-20', '2026-11-05');

INSERT INTO purchase_order_items (order_number, article_code, quantity, position) VALUES
    (1, 'CAU-001', 500, 1),
    (1, 'AZU-002', 200, 2);

-- Pedido 2: Insumos Andinos, creado 2026-10-22, entrega 2026-11-10
INSERT INTO purchase_orders (number, supplier_cuit, created_at, expected_delivery) VALUES
    (2, '20234567891', '2026-10-22', '2026-11-10');

INSERT INTO purchase_order_items (order_number, article_code, quantity, position) VALUES
    (2, 'NEG-003', 50, 1);

-- Pedido 3: Cauchos del Sur, creado 2026-10-25, entrega 2026-11-12
INSERT INTO purchase_orders (number, supplier_cuit, created_at, expected_delivery) VALUES
    (3, '30712345678', '2026-10-25', '2026-11-12');

INSERT INTO purchase_order_items (order_number, article_code, quantity, position) VALUES
    (3, 'ACE-004', 120, 1);
