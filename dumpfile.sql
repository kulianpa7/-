--
-- PostgreSQL database dump
--

-- Dumped from database version 16.6
-- Dumped by pg_dump version 16.6

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: adminpack; Type: EXTENSION; Schema: -; Owner: -
--

CREATE EXTENSION IF NOT EXISTS adminpack WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION adminpack; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION adminpack IS 'administrative functions for PostgreSQL';


SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: car; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.car (
    id integer NOT NULL,
    car_number character varying NOT NULL,
    can_passenger integer NOT NULL,
    car_situation_id integer NOT NULL,
    is_del integer DEFAULT 0 NOT NULL
);


ALTER TABLE public.car OWNER TO postgres;

--
-- Name: car_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.car_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.car_id_seq OWNER TO postgres;

--
-- Name: car_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.car_id_seq OWNED BY public.car.id;


--
-- Name: driver; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.driver (
    id integer NOT NULL,
    name character varying NOT NULL,
    phone character varying NOT NULL,
    username character varying NOT NULL,
    password character varying NOT NULL,
    is_del integer DEFAULT 0 NOT NULL
);


ALTER TABLE public.driver OWNER TO postgres;

--
-- Name: driver_car_scheduling; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.driver_car_scheduling (
    id integer NOT NULL,
    date date,
    time_id integer,
    driver_id integer,
    car_id integer,
    time_code integer
);


ALTER TABLE public.driver_car_scheduling OWNER TO postgres;

--
-- Name: driver_car_scheduling_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.driver_car_scheduling_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.driver_car_scheduling_id_seq OWNER TO postgres;

--
-- Name: driver_car_scheduling_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.driver_car_scheduling_id_seq OWNED BY public.driver_car_scheduling.id;


--
-- Name: driver_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.driver_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.driver_id_seq OWNER TO postgres;

--
-- Name: driver_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.driver_id_seq OWNED BY public.driver.id;


--
-- Name: logger; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.logger (
    id integer NOT NULL,
    description character varying(5000) DEFAULT NULL::character varying
);


ALTER TABLE public.logger OWNER TO postgres;

--
-- Name: logger_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.logger_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.logger_id_seq OWNER TO postgres;

--
-- Name: logger_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.logger_id_seq OWNED BY public.logger.id;


--
-- Name: order_status; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.order_status (
    id integer NOT NULL,
    status character varying(500)
);


ALTER TABLE public.order_status OWNER TO postgres;

--
-- Name: orders; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.orders (
    id integer NOT NULL,
    passenger_name character varying NOT NULL,
    phone character varying NOT NULL,
    how_many character varying NOT NULL,
    date_time timestamp without time zone NOT NULL,
    driver_id integer NOT NULL,
    order_status integer NOT NULL,
    driver_car_scheduling_id integer,
    car_id integer,
    is_del integer DEFAULT 0,
    "position" character varying(255)
);


ALTER TABLE public.orders OWNER TO postgres;

--
-- Name: orders_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.orders_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.orders_id_seq OWNER TO postgres;

--
-- Name: orders_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.orders_id_seq OWNED BY public.orders.id;


--
-- Name: roles; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.roles (
    id integer NOT NULL,
    name character varying(50) DEFAULT NULL::character varying,
    role boolean,
    backend_staff boolean,
    driver boolean,
    driver_schedule boolean,
    order_arrangement boolean,
    order_list boolean
);


ALTER TABLE public.roles OWNER TO postgres;

--
-- Name: roles_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.roles_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.roles_id_seq OWNER TO postgres;

--
-- Name: roles_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.roles_id_seq OWNED BY public.roles.id;


--
-- Name: time; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."time" (
    id integer NOT NULL,
    time_code integer DEFAULT 0 NOT NULL,
    start_time time without time zone NOT NULL,
    end_time time without time zone NOT NULL
);


ALTER TABLE public."time" OWNER TO postgres;

--
-- Name: time_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.time_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.time_id_seq OWNER TO postgres;

--
-- Name: time_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.time_id_seq OWNED BY public."time".id;


--
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    id integer NOT NULL,
    users character varying(50) DEFAULT 'NONE'::character varying,
    role_id integer,
    username character varying(50) NOT NULL,
    password character varying(255) NOT NULL,
    is_del integer DEFAULT 0 NOT NULL
);


ALTER TABLE public.users OWNER TO postgres;

--
-- Name: user_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.user_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public.user_id_seq OWNER TO postgres;

--
-- Name: user_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.user_id_seq OWNED BY public.users.id;


--
-- Name: car id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.car ALTER COLUMN id SET DEFAULT nextval('public.car_id_seq'::regclass);


--
-- Name: driver id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.driver ALTER COLUMN id SET DEFAULT nextval('public.driver_id_seq'::regclass);


--
-- Name: driver_car_scheduling id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.driver_car_scheduling ALTER COLUMN id SET DEFAULT nextval('public.driver_car_scheduling_id_seq'::regclass);


--
-- Name: logger id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.logger ALTER COLUMN id SET DEFAULT nextval('public.logger_id_seq'::regclass);


--
-- Name: orders id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders ALTER COLUMN id SET DEFAULT nextval('public.orders_id_seq'::regclass);


--
-- Name: roles id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.roles ALTER COLUMN id SET DEFAULT nextval('public.roles_id_seq'::regclass);


--
-- Name: time id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."time" ALTER COLUMN id SET DEFAULT nextval('public.time_id_seq'::regclass);


--
-- Name: users id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users ALTER COLUMN id SET DEFAULT nextval('public.user_id_seq'::regclass);


--
-- Data for Name: car; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.car (id, car_number, can_passenger, car_situation_id, is_del) FROM stdin;
5	BCB-1212	5	1	0
7	BCD-1313	6	1	0
6	BCD-1414	5	1	0
3	CDS-1323	5	1	1
4	ABS-2293	5	0	1
\.


--
-- Data for Name: driver; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.driver (id, name, phone, username, password, is_del) FROM stdin;
3	丁丁1	0987654321	test	9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08	0
5	丁丁2	test	test2	9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08	0
6	丁丁3	test	test3	9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08	0
7	丁丁ˋ4	test	test4	9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08	0
4	丁丁5	000000000000000000000000000000000000000000	tersttttttttttttttttttttttttttttttttttt	9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08	0
\.


--
-- Data for Name: driver_car_scheduling; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.driver_car_scheduling (id, date, time_id, driver_id, car_id, time_code) FROM stdin;
148	2024-12-01	1	3	5	0
149	2024-12-02	1	3	5	0
150	2024-12-02	2	3	5	1
151	2024-12-03	1	3	5	0
152	2024-12-08	1	3	5	0
153	2024-12-09	1	3	5	0
154	2024-12-09	2	3	5	1
155	2024-12-15	1	3	5	0
156	2024-12-18	1	3	5	0
157	2024-12-19	1	3	5	0
158	2024-12-20	1	3	5	0
159	2024-12-22	1	3	5	0
160	2024-12-23	1	3	5	0
161	2024-12-23	2	3	5	1
162	2024-12-24	1	3	5	0
163	2024-12-25	1	3	5	0
164	2024-12-26	1	3	5	0
165	2024-12-27	1	3	5	0
166	2024-12-29	1	3	5	0
167	2024-12-30	1	3	5	0
168	2024-12-30	2	3	5	1
169	2024-12-31	1	3	5	0
\.


--
-- Data for Name: logger; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.logger (id, description) FROM stdin;
\.


--
-- Data for Name: order_status; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.order_status (id, status) FROM stdin;
-1	尚未開始
0	開始
1	結束
2	棄單
\.


--
-- Data for Name: orders; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.orders (id, passenger_name, phone, how_many, date_time, driver_id, order_status, driver_car_scheduling_id, car_id, is_del, "position") FROM stdin;
3	吳宗憲哥	0987	5	2024-12-24 14:01:12	5	2	\N	5	0	xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
\.


--
-- Data for Name: roles; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.roles (id, name, role, backend_staff, driver, driver_schedule, order_arrangement, order_list) FROM stdin;
18	訪客3	f	f	f	f	f	t
17	超級管理員	t	t	t	t	t	t
20	老闆	f	t	t	t	t	t
19	排班人員	f	f	f	t	t	f
\.


--
-- Data for Name: time; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."time" (id, time_code, start_time, end_time) FROM stdin;
1	0	00:00:00	08:00:00
2	1	08:00:01	16:00:00
4	2	16:00:01	23:59:59
\.


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.users (id, users, role_id, username, password, is_del) FROM stdin;
3	丁丁	17	test	9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08	0
4	丁丁2	20	test2	60303ae22b998861bce3b28f33eec1be758a213c86c93c076dbe9f558c11c752	0
11	ppoo	20	pop8	2f0495d20264215f704035e702e1ce85d44c0c02577249f5b91d5f7892137083	1
13	test	18	test	9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08	1
14	test	18	s	9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08	1
15	tests	18	tests	59830ebc3a4184110566bf1a290d08473dfdcbd492ce498b14cd1a5e2fa2e441	1
16	test	18	tests	9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08	1
\.


--
-- Name: car_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.car_id_seq', 7, true);


--
-- Name: driver_car_scheduling_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.driver_car_scheduling_id_seq', 169, true);


--
-- Name: driver_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.driver_id_seq', 7, true);


--
-- Name: logger_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.logger_id_seq', 1, false);


--
-- Name: orders_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.orders_id_seq', 3, true);


--
-- Name: roles_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.roles_id_seq', 23, true);


--
-- Name: time_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.time_id_seq', 4, true);


--
-- Name: user_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.user_id_seq', 16, true);


--
-- Name: car car_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.car
    ADD CONSTRAINT car_pkey PRIMARY KEY (id);


--
-- Name: driver_car_scheduling driver_car_scheduling_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.driver_car_scheduling
    ADD CONSTRAINT driver_car_scheduling_pkey PRIMARY KEY (id);


--
-- Name: driver driver_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.driver
    ADD CONSTRAINT driver_pkey PRIMARY KEY (id);


--
-- Name: order_status order_status_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.order_status
    ADD CONSTRAINT order_status_pkey PRIMARY KEY (id);


--
-- Name: orders orders_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_pkey PRIMARY KEY (id);


--
-- Name: roles roles_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.roles
    ADD CONSTRAINT roles_pkey PRIMARY KEY (id);


--
-- Name: time time_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."time"
    ADD CONSTRAINT time_pkey PRIMARY KEY (id);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- Name: driver_car_scheduling FK__car; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.driver_car_scheduling
    ADD CONSTRAINT "FK__car" FOREIGN KEY (car_id) REFERENCES public.car(id) ON UPDATE CASCADE ON DELETE SET NULL;


--
-- Name: driver_car_scheduling FK__driver; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.driver_car_scheduling
    ADD CONSTRAINT "FK__driver" FOREIGN KEY (driver_id) REFERENCES public.driver(id) ON UPDATE CASCADE ON DELETE SET NULL;


--
-- Name: users FK__roles; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT "FK__roles" FOREIGN KEY (role_id) REFERENCES public.roles(id) ON UPDATE CASCADE ON DELETE SET NULL;


--
-- Name: driver_car_scheduling FK__time; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.driver_car_scheduling
    ADD CONSTRAINT "FK__time" FOREIGN KEY (time_id) REFERENCES public."time"(id) ON UPDATE CASCADE ON DELETE SET NULL;


--
-- Name: orders FK_orders_car; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT "FK_orders_car" FOREIGN KEY (car_id) REFERENCES public.car(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- Name: orders FK_orders_driver; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT "FK_orders_driver" FOREIGN KEY (driver_id) REFERENCES public.driver(id) ON UPDATE CASCADE ON DELETE SET NULL;


--
-- Name: orders FK_orders_driver_car_scheduling; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT "FK_orders_driver_car_scheduling" FOREIGN KEY (driver_car_scheduling_id) REFERENCES public.driver_car_scheduling(id) ON UPDATE CASCADE ON DELETE SET NULL;


--
-- Name: orders FK_orders_order_status; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT "FK_orders_order_status" FOREIGN KEY (order_status) REFERENCES public.order_status(id) ON UPDATE CASCADE ON DELETE SET NULL;


--
-- PostgreSQL database dump complete
--

