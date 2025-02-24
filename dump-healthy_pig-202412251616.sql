PGDMP                      |            healthy_pig    16.3    16.3 H    B           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false            C           0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false            D           0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false            E           1262    25819    healthy_pig    DATABASE     �   CREATE DATABASE healthy_pig WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE_PROVIDER = libc LOCALE = 'Chinese (Traditional)_Taiwan.950';
    DROP DATABASE healthy_pig;
                postgres    false                        2615    2200    public    SCHEMA        CREATE SCHEMA public;
    DROP SCHEMA public;
                pg_database_owner    false            F           0    0    SCHEMA public    COMMENT     6   COMMENT ON SCHEMA public IS 'standard public schema';
                   pg_database_owner    false    5            �            1259    25830    car    TABLE     �   CREATE TABLE public.car (
    id integer NOT NULL,
    car_number character varying NOT NULL,
    can_passenger integer NOT NULL,
    car_situation_id integer NOT NULL,
    is_del integer DEFAULT 0 NOT NULL
);
    DROP TABLE public.car;
       public         heap    postgres    false    5            �            1259    25836 
   car_id_seq    SEQUENCE     �   CREATE SEQUENCE public.car_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 !   DROP SEQUENCE public.car_id_seq;
       public          postgres    false    5    216            G           0    0 
   car_id_seq    SEQUENCE OWNED BY     9   ALTER SEQUENCE public.car_id_seq OWNED BY public.car.id;
          public          postgres    false    217            �            1259    25837    driver    TABLE     �   CREATE TABLE public.driver (
    id integer NOT NULL,
    name character varying NOT NULL,
    phone character varying NOT NULL,
    username character varying NOT NULL,
    password character varying NOT NULL,
    is_del integer DEFAULT 0 NOT NULL
);
    DROP TABLE public.driver;
       public         heap    postgres    false    5            �            1259    25843    driver_car_scheduling    TABLE     �   CREATE TABLE public.driver_car_scheduling (
    id integer NOT NULL,
    date date,
    time_id integer,
    driver_id integer,
    car_id integer,
    time_code integer
);
 )   DROP TABLE public.driver_car_scheduling;
       public         heap    postgres    false    5            �            1259    25846    driver_car_scheduling_id_seq    SEQUENCE     �   CREATE SEQUENCE public.driver_car_scheduling_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 3   DROP SEQUENCE public.driver_car_scheduling_id_seq;
       public          postgres    false    219    5            H           0    0    driver_car_scheduling_id_seq    SEQUENCE OWNED BY     ]   ALTER SEQUENCE public.driver_car_scheduling_id_seq OWNED BY public.driver_car_scheduling.id;
          public          postgres    false    220            �            1259    25847    driver_id_seq    SEQUENCE     �   CREATE SEQUENCE public.driver_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 $   DROP SEQUENCE public.driver_id_seq;
       public          postgres    false    218    5            I           0    0    driver_id_seq    SEQUENCE OWNED BY     ?   ALTER SEQUENCE public.driver_id_seq OWNED BY public.driver.id;
          public          postgres    false    221            �            1259    25848    logger    TABLE     �   CREATE TABLE public.logger (
    id integer NOT NULL,
    description character varying(5000) DEFAULT NULL::character varying
);
    DROP TABLE public.logger;
       public         heap    postgres    false    5            �            1259    25854    logger_id_seq    SEQUENCE     �   CREATE SEQUENCE public.logger_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 $   DROP SEQUENCE public.logger_id_seq;
       public          postgres    false    222    5            J           0    0    logger_id_seq    SEQUENCE OWNED BY     ?   ALTER SEQUENCE public.logger_id_seq OWNED BY public.logger.id;
          public          postgres    false    223            �            1259    25855    order_status    TABLE     a   CREATE TABLE public.order_status (
    id integer NOT NULL,
    status character varying(500)
);
     DROP TABLE public.order_status;
       public         heap    postgres    false    5            �            1259    25858    orders    TABLE     �  CREATE TABLE public.orders (
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
    DROP TABLE public.orders;
       public         heap    postgres    false    5            �            1259    25864    orders_id_seq    SEQUENCE     �   CREATE SEQUENCE public.orders_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 $   DROP SEQUENCE public.orders_id_seq;
       public          postgres    false    225    5            K           0    0    orders_id_seq    SEQUENCE OWNED BY     ?   ALTER SEQUENCE public.orders_id_seq OWNED BY public.orders.id;
          public          postgres    false    226            �            1259    25865    roles    TABLE       CREATE TABLE public.roles (
    id integer NOT NULL,
    name character varying(50) DEFAULT NULL::character varying,
    role boolean,
    backend_staff boolean,
    driver boolean,
    driver_schedule boolean,
    order_arrangement boolean,
    order_list boolean
);
    DROP TABLE public.roles;
       public         heap    postgres    false    5            �            1259    25869    roles_id_seq    SEQUENCE     �   CREATE SEQUENCE public.roles_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 #   DROP SEQUENCE public.roles_id_seq;
       public          postgres    false    5    227            L           0    0    roles_id_seq    SEQUENCE OWNED BY     =   ALTER SEQUENCE public.roles_id_seq OWNED BY public.roles.id;
          public          postgres    false    228            �            1259    25870    time    TABLE     �   CREATE TABLE public."time" (
    id integer NOT NULL,
    time_code integer DEFAULT 0 NOT NULL,
    start_time time without time zone NOT NULL,
    end_time time without time zone NOT NULL
);
    DROP TABLE public."time";
       public         heap    postgres    false    5            �            1259    25874    time_id_seq    SEQUENCE     �   CREATE SEQUENCE public.time_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 "   DROP SEQUENCE public.time_id_seq;
       public          postgres    false    5    229            M           0    0    time_id_seq    SEQUENCE OWNED BY     =   ALTER SEQUENCE public.time_id_seq OWNED BY public."time".id;
          public          postgres    false    230            �            1259    25875    users    TABLE       CREATE TABLE public.users (
    id integer NOT NULL,
    users character varying(50) DEFAULT 'NONE'::character varying,
    role_id integer,
    username character varying(50) NOT NULL,
    password character varying(255) NOT NULL,
    is_del integer DEFAULT 0 NOT NULL
);
    DROP TABLE public.users;
       public         heap    postgres    false    5            �            1259    25880    user_id_seq    SEQUENCE     �   CREATE SEQUENCE public.user_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 "   DROP SEQUENCE public.user_id_seq;
       public          postgres    false    5    231            N           0    0    user_id_seq    SEQUENCE OWNED BY     <   ALTER SEQUENCE public.user_id_seq OWNED BY public.users.id;
          public          postgres    false    232            x           2604    25881    car id    DEFAULT     `   ALTER TABLE ONLY public.car ALTER COLUMN id SET DEFAULT nextval('public.car_id_seq'::regclass);
 5   ALTER TABLE public.car ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    217    216            z           2604    25882 	   driver id    DEFAULT     f   ALTER TABLE ONLY public.driver ALTER COLUMN id SET DEFAULT nextval('public.driver_id_seq'::regclass);
 8   ALTER TABLE public.driver ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    221    218            |           2604    25883    driver_car_scheduling id    DEFAULT     �   ALTER TABLE ONLY public.driver_car_scheduling ALTER COLUMN id SET DEFAULT nextval('public.driver_car_scheduling_id_seq'::regclass);
 G   ALTER TABLE public.driver_car_scheduling ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    220    219            }           2604    25884 	   logger id    DEFAULT     f   ALTER TABLE ONLY public.logger ALTER COLUMN id SET DEFAULT nextval('public.logger_id_seq'::regclass);
 8   ALTER TABLE public.logger ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    223    222                       2604    25885 	   orders id    DEFAULT     f   ALTER TABLE ONLY public.orders ALTER COLUMN id SET DEFAULT nextval('public.orders_id_seq'::regclass);
 8   ALTER TABLE public.orders ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    226    225            �           2604    25886    roles id    DEFAULT     d   ALTER TABLE ONLY public.roles ALTER COLUMN id SET DEFAULT nextval('public.roles_id_seq'::regclass);
 7   ALTER TABLE public.roles ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    228    227            �           2604    25887    time id    DEFAULT     d   ALTER TABLE ONLY public."time" ALTER COLUMN id SET DEFAULT nextval('public.time_id_seq'::regclass);
 8   ALTER TABLE public."time" ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    230    229            �           2604    25888    users id    DEFAULT     c   ALTER TABLE ONLY public.users ALTER COLUMN id SET DEFAULT nextval('public.user_id_seq'::regclass);
 7   ALTER TABLE public.users ALTER COLUMN id DROP DEFAULT;
       public          postgres    false    232    231            /          0    25830    car 
   TABLE DATA                 public          postgres    false    216   �N       1          0    25837    driver 
   TABLE DATA                 public          postgres    false    218   �O       2          0    25843    driver_car_scheduling 
   TABLE DATA                 public          postgres    false    219   [P       5          0    25848    logger 
   TABLE DATA                 public          postgres    false    222   �S       7          0    25855    order_status 
   TABLE DATA                 public          postgres    false    224   �S       8          0    25858    orders 
   TABLE DATA                 public          postgres    false    225   IT       :          0    25865    roles 
   TABLE DATA                 public          postgres    false    227   �T       <          0    25870    time 
   TABLE DATA                 public          postgres    false    229   hU       >          0    25875    users 
   TABLE DATA                 public          postgres    false    231   �U       O           0    0 
   car_id_seq    SEQUENCE SET     8   SELECT pg_catalog.setval('public.car_id_seq', 7, true);
          public          postgres    false    217            P           0    0    driver_car_scheduling_id_seq    SEQUENCE SET     L   SELECT pg_catalog.setval('public.driver_car_scheduling_id_seq', 860, true);
          public          postgres    false    220            Q           0    0    driver_id_seq    SEQUENCE SET     ;   SELECT pg_catalog.setval('public.driver_id_seq', 7, true);
          public          postgres    false    221            R           0    0    logger_id_seq    SEQUENCE SET     <   SELECT pg_catalog.setval('public.logger_id_seq', 1, false);
          public          postgres    false    223            S           0    0    orders_id_seq    SEQUENCE SET     ;   SELECT pg_catalog.setval('public.orders_id_seq', 3, true);
          public          postgres    false    226            T           0    0    roles_id_seq    SEQUENCE SET     ;   SELECT pg_catalog.setval('public.roles_id_seq', 26, true);
          public          postgres    false    228            U           0    0    time_id_seq    SEQUENCE SET     9   SELECT pg_catalog.setval('public.time_id_seq', 4, true);
          public          postgres    false    230            V           0    0    user_id_seq    SEQUENCE SET     :   SELECT pg_catalog.setval('public.user_id_seq', 17, true);
          public          postgres    false    232            �           2606    25890    car car_pkey 
   CONSTRAINT     J   ALTER TABLE ONLY public.car
    ADD CONSTRAINT car_pkey PRIMARY KEY (id);
 6   ALTER TABLE ONLY public.car DROP CONSTRAINT car_pkey;
       public            postgres    false    216            �           2606    25892 0   driver_car_scheduling driver_car_scheduling_pkey 
   CONSTRAINT     n   ALTER TABLE ONLY public.driver_car_scheduling
    ADD CONSTRAINT driver_car_scheduling_pkey PRIMARY KEY (id);
 Z   ALTER TABLE ONLY public.driver_car_scheduling DROP CONSTRAINT driver_car_scheduling_pkey;
       public            postgres    false    219            �           2606    25894    driver driver_pkey 
   CONSTRAINT     P   ALTER TABLE ONLY public.driver
    ADD CONSTRAINT driver_pkey PRIMARY KEY (id);
 <   ALTER TABLE ONLY public.driver DROP CONSTRAINT driver_pkey;
       public            postgres    false    218            �           2606    25896    order_status order_status_pkey 
   CONSTRAINT     \   ALTER TABLE ONLY public.order_status
    ADD CONSTRAINT order_status_pkey PRIMARY KEY (id);
 H   ALTER TABLE ONLY public.order_status DROP CONSTRAINT order_status_pkey;
       public            postgres    false    224            �           2606    25898    orders orders_pkey 
   CONSTRAINT     P   ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_pkey PRIMARY KEY (id);
 <   ALTER TABLE ONLY public.orders DROP CONSTRAINT orders_pkey;
       public            postgres    false    225            �           2606    25900    roles roles_pkey 
   CONSTRAINT     N   ALTER TABLE ONLY public.roles
    ADD CONSTRAINT roles_pkey PRIMARY KEY (id);
 :   ALTER TABLE ONLY public.roles DROP CONSTRAINT roles_pkey;
       public            postgres    false    227            �           2606    25902    time time_pkey 
   CONSTRAINT     N   ALTER TABLE ONLY public."time"
    ADD CONSTRAINT time_pkey PRIMARY KEY (id);
 :   ALTER TABLE ONLY public."time" DROP CONSTRAINT time_pkey;
       public            postgres    false    229            �           2606    25904    users users_pkey 
   CONSTRAINT     N   ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);
 :   ALTER TABLE ONLY public.users DROP CONSTRAINT users_pkey;
       public            postgres    false    231            �           2606    25905    driver_car_scheduling FK__car    FK CONSTRAINT     �   ALTER TABLE ONLY public.driver_car_scheduling
    ADD CONSTRAINT "FK__car" FOREIGN KEY (car_id) REFERENCES public.car(id) ON UPDATE CASCADE ON DELETE SET NULL;
 I   ALTER TABLE ONLY public.driver_car_scheduling DROP CONSTRAINT "FK__car";
       public          postgres    false    219    216    4745            �           2606    25910     driver_car_scheduling FK__driver    FK CONSTRAINT     �   ALTER TABLE ONLY public.driver_car_scheduling
    ADD CONSTRAINT "FK__driver" FOREIGN KEY (driver_id) REFERENCES public.driver(id) ON UPDATE CASCADE ON DELETE SET NULL;
 L   ALTER TABLE ONLY public.driver_car_scheduling DROP CONSTRAINT "FK__driver";
       public          postgres    false    4747    218    219            �           2606    25915    users FK__roles    FK CONSTRAINT     �   ALTER TABLE ONLY public.users
    ADD CONSTRAINT "FK__roles" FOREIGN KEY (role_id) REFERENCES public.roles(id) ON UPDATE CASCADE ON DELETE SET NULL;
 ;   ALTER TABLE ONLY public.users DROP CONSTRAINT "FK__roles";
       public          postgres    false    231    4755    227            �           2606    25920    driver_car_scheduling FK__time    FK CONSTRAINT     �   ALTER TABLE ONLY public.driver_car_scheduling
    ADD CONSTRAINT "FK__time" FOREIGN KEY (time_id) REFERENCES public."time"(id) ON UPDATE CASCADE ON DELETE SET NULL;
 J   ALTER TABLE ONLY public.driver_car_scheduling DROP CONSTRAINT "FK__time";
       public          postgres    false    4757    229    219            �           2606    25925    orders FK_orders_car    FK CONSTRAINT     �   ALTER TABLE ONLY public.orders
    ADD CONSTRAINT "FK_orders_car" FOREIGN KEY (car_id) REFERENCES public.car(id) ON UPDATE CASCADE ON DELETE CASCADE;
 @   ALTER TABLE ONLY public.orders DROP CONSTRAINT "FK_orders_car";
       public          postgres    false    216    225    4745            �           2606    25930    orders FK_orders_driver    FK CONSTRAINT     �   ALTER TABLE ONLY public.orders
    ADD CONSTRAINT "FK_orders_driver" FOREIGN KEY (driver_id) REFERENCES public.driver(id) ON UPDATE CASCADE ON DELETE SET NULL;
 C   ALTER TABLE ONLY public.orders DROP CONSTRAINT "FK_orders_driver";
       public          postgres    false    218    225    4747            �           2606    25935 &   orders FK_orders_driver_car_scheduling    FK CONSTRAINT     �   ALTER TABLE ONLY public.orders
    ADD CONSTRAINT "FK_orders_driver_car_scheduling" FOREIGN KEY (driver_car_scheduling_id) REFERENCES public.driver_car_scheduling(id) ON UPDATE CASCADE ON DELETE SET NULL;
 R   ALTER TABLE ONLY public.orders DROP CONSTRAINT "FK_orders_driver_car_scheduling";
       public          postgres    false    4749    219    225            �           2606    25940    orders FK_orders_order_status    FK CONSTRAINT     �   ALTER TABLE ONLY public.orders
    ADD CONSTRAINT "FK_orders_order_status" FOREIGN KEY (order_status) REFERENCES public.order_status(id) ON UPDATE CASCADE ON DELETE SET NULL;
 I   ALTER TABLE ONLY public.orders DROP CONSTRAINT "FK_orders_order_status";
       public          postgres    false    4751    225    224            /   y   x���v
Q���W((M��L�KN,Rs�	uV�0�QPwrv�5424R�Q ru4��<��3�s�5464�3#V�L���	)��9��32��3$�����)X����� ��� �*E�      1   �   x���v
Q���W((M��L�K)�,K-Rs�	uV�0�QP���ՁLKs3Sc#0�$��D[�Y��XZX�$����Z&��&&$��&��&'���&%$Y%����%�&�$X �0д��$�S�k����Ftu��!��1��C��9�m���:��SpR!@�[T\BP�C\\ +�#      2   L  x����jAF�y��E�F����W.�H�M��H$>����og�z�C��s�gj�������������������������Wן�~\��y����e����Ӌ�E�ێ�h=9)r��d��nk���|}t�����z��� ��	@��� ��`@I���E�& {ZpD`�}K���0�"	���L �R�$ c)�p�X�&܇3��	��h�n3c)����X�f܇�͸��R��!�{�<�KA`��y@�@�>�EȮ�"��a��� ld�{�-�2Ȯ�#�'\É@r�����6]�R�WE ����o_]*��R�$\�X�$l�2�*�R8�L�+�X�$l�*dWKIx$�Kyz$f�+Y���kG �¥��p�R6X�$�m)%a�5A ��X�&l�fdWKIx��Kyz�b�;Y�X��#�n�@v��Mx$��M�`� �T�K)	l5�+\JI�`kC �¥��ץ����d�c)�O�z+$W�b)�?��쫌�I�8̾�@v���5���o ��>��=�Ud�=�Cj���Ș�x�}�r�f_#㋏E �ld��R�ɒ��@V�#�U^J�)/�@Vy"�T���=�EH*�"�U��.�T����r,%�ۨ�@ ��d�c)	�4ׂ@RY����R�޺Y�@Vy)�5s�d�Y��k��D �l���-�$�˦d����RJ¹l��rG �KI����#�U�$�k,%a��UH*WE �Kф7�Z�*7�ʱ����xd����RJ¹�
I�&$��RJ���rE �KI�pz�d�Y�X�%�I��@R�.�GG� q�*      5   
   x���          7   h   x���v
Q���W((M��L��/JI-�/.I,)-Vs�	uV��5�QP�aֳ9�^N�~��[]Ӛ˓H�@�����|�gs瓢����▧�ցtqq ��O�      8   r   x���v
Q���W((M��L��/JI-*Vs�	uV�0�QP:a��uӟ�mz:y�:�o`ia�MA�������������������P�TG�HG�/���6 *���5���� �,�      :   �   x���v
Q���W((M��L�+��I-Vs�	uV�0��QP�b��u���u�s�S�S%E����\��L62 ����rz�:�f\$1�Z}�7�y��'�v=�����e�9���Z�o��|���� �s4��\\ ¯      <   a   x���v
Q���W((M��L�S*��MURs�	uV�0�Q0�QP70�#u��ִ��$h����!B�!� C3R0�Q0Bh`dlej	D �� .?/7      >     x���Aj\1��s��{-�"ɒ-�UYSh��mY�@a��� �K�W��{�/i(�΢����O���_]~�������~��w��-����˫���4���|1��pԡg��YE&���!�' Gs��l`@�q�R3���0$�0����7��av������������l�EɅ��&R��P;w�T�*�5��B(�g� ˫���}yY��d��BaTF��v,�a�q
�7��3�s֊<(�8�BΌg#Ŀ���6a���Y3��8���	�%�z�#ŉjΪ�y��=w��I���7���A���XQC�$t.Ó�ϯߞ;����N �:ͽE,eT�R���R�BL
Y,SSP�5T1J�F�X�p�l~Vn#�     