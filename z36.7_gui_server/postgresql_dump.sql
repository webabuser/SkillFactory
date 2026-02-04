--
-- PostgreSQL database dump
--

-- Dumped from database version 10.23 (Ubuntu 10.23-0ubuntu0.18.04.2)
-- Dumped by pg_dump version 10.23 (Ubuntu 10.23-0ubuntu0.18.04.2)

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
-- Name: message_status_flag; Type: TYPE; Schema: public; Owner: alex
--

CREATE TYPE public.message_status_flag AS ENUM (
    'sent',
    'read',
    'unread',
    'deleted',
    'received'
);


ALTER TYPE public.message_status_flag OWNER TO alex;

--
-- Name: status_type; Type: TYPE; Schema: public; Owner: alex
--

CREATE TYPE public.status_type AS ENUM (
    'active',
    'blocked',
    'deleted'
);


ALTER TYPE public.status_type OWNER TO alex;

--
-- Name: add_user_to_hash(); Type: FUNCTION; Schema: public; Owner: alex
--

CREATE FUNCTION public.add_user_to_hash() RETURNS trigger
    LANGUAGE plpgsql
    AS $$BEGIN
INSERT INTO hashes (user_id, hash) VALUES (NEW.id, NULL);
RETURN NEW;
END;
$$;


ALTER FUNCTION public.add_user_to_hash() OWNER TO alex;

--
-- Name: date_format(timestamp without time zone, text); Type: FUNCTION; Schema: public; Owner: alex
--

CREATE FUNCTION public.date_format(timestamp without time zone, text) RETURNS text
    LANGUAGE plpgsql
    AS $_$
BEGIN
    RETURN TO_CHAR($1, 
        REPLACE(
            REPLACE(
                REPLACE(
                    REPLACE($2, '%Y', 'YYYY'),
                    '%m', 'MM'),
                '%d', 'DD'),
            '%H:%i', 'HH24:MI')
    );
END;
$_$;


ALTER FUNCTION public.date_format(timestamp without time zone, text) OWNER TO alex;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: hashes; Type: TABLE; Schema: public; Owner: alex
--

CREATE TABLE public.hashes (
    id integer NOT NULL,
    user_id integer,
    hash character(40)
);


ALTER TABLE public.hashes OWNER TO alex;

--
-- Name: TABLE hashes; Type: COMMENT; Schema: public; Owner: alex
--

COMMENT ON TABLE public.hashes IS 'Таблица хэшпаролей';


--
-- Name: messages; Type: TABLE; Schema: public; Owner: alex
--

CREATE TABLE public.messages (
    id integer NOT NULL,
    sender_id integer,
    receiver_id integer,
    text text,
    created timestamp without time zone DEFAULT CURRENT_TIMESTAMP,
    status public.message_status_flag DEFAULT 'unread'::public.message_status_flag NOT NULL
);


ALTER TABLE public.messages OWNER TO alex;

--
-- Name: TABLE messages; Type: COMMENT; Schema: public; Owner: alex
--

COMMENT ON TABLE public.messages IS 'Таблица сообщений';


--
-- Name: users; Type: TABLE; Schema: public; Owner: alex
--

CREATE TABLE public.users (
    id integer NOT NULL,
    login character varying(50) NOT NULL,
    name character varying(100),
    surname character varying(100),
    email character varying(100),
    created timestamp without time zone DEFAULT CURRENT_TIMESTAMP NOT NULL,
    status public.status_type DEFAULT 'active'::public.status_type NOT NULL,
    blocked_at timestamp without time zone,
    block_reason text
);


ALTER TABLE public.users OWNER TO alex;

--
-- Name: TABLE users; Type: COMMENT; Schema: public; Owner: alex
--

COMMENT ON TABLE public.users IS 'Таблица зарегистрированных пользователей';


--
-- Data for Name: hashes; Type: TABLE DATA; Schema: public; Owner: alex
--

INSERT INTO public.hashes VALUES (1, 1, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (2, 2, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (3, 3, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (4, 4, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (5, 5, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (6, 6, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (7, 7, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (8, 8, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (9, 9, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (10, 10, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (11, 11, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (12, 12, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (13, 13, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (14, 14, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (15, 15, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (16, 16, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (17, 17, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (18, 18, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (19, 19, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (20, 20, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (21, 21, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (22, 22, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (23, 23, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (24, 24, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (25, 25, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (26, 26, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (27, 27, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (28, 28, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (29, 29, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');
INSERT INTO public.hashes VALUES (30, 30, '40bd001563085fc35165329ea1ff5c5ecbdbbeef');


--
-- Data for Name: messages; Type: TABLE DATA; Schema: public; Owner: alex
--

INSERT INTO public.messages VALUES (1, 1, 2, 'Привет!', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (2, 2, 1, 'Как дела?', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (3, 1, 3, 'Ок', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (4, 3, 2, 'Спасибо', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (5, 2, 3, 'Договорились', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (6, 1, 4, 'Привет, как дела?', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (7, 4, 1, 'Хорошо, спасибо!', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (8, 2, 5, 'Помоги с проектом', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (9, 5, 2, 'Конечно', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (10, 3, 6, 'Отличная работа!', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (11, 1, 10, 'Здравствуйте! У меня есть предложения по улучшению проекта.', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (12, 10, 1, 'Спасибо за предложения! Давайте обсудим.', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (13, 11, 12, 'Привет!', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (14, 12, 13, 'Как дела?', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (15, 13, 14, 'Нормально', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (16, 14, 15, 'Спасибо', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (17, 15, 16, 'Пожалуйста', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (18, 1, 0, 'Всем привет!', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (19, 2, 0, 'Добрый день!', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (20, 3, 0, 'Важное объявление', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (21, 1, 5, 'Как проект?', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (22, 1, 8, 'Нужна помощь', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (23, 1, 12, 'Созвонимся?', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (24, 2, 7, 'Проверь почту', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (25, 2, 9, 'Спасибо!', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (26, 3, 4, 'Все получил', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (27, 3, 11, 'Отличная идея!', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (28, 4, 6, 'Давай обсудим', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (29, 4, 14, 'Жду звонка', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (30, 5, 3, 'Договорились', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (31, 6, 2, 'Спасибо за совет!', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (32, 7, 1, 'Рад помочь!', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (33, 8, 10, 'Все понял', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (34, 9, 15, 'Отправляю файлы', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (35, 10, 20, 'Получил, спасибо!', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (36, 11, 25, 'Как настроение?', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (37, 12, 30, 'Все супер!', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (38, 13, 1, 'Работаем дальше', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (39, 14, 2, 'Согласен', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (40, 15, 3, 'Интересно', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (41, 16, 4, 'Нужно подумать', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (42, 17, 5, 'Давай встретимся', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (43, 18, 6, 'Хорошо, в 15:00', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (44, 19, 7, 'Не забудь документы', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (45, 20, 8, 'Уже подготовил', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (46, 21, 9, 'Все готово?', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (47, 22, 10, 'Почти закончил', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (48, 23, 11, 'Жду ответа', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (49, 24, 12, 'Отвечаю сейчас', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (50, 25, 13, 'Спасибо за информацию', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (51, 26, 14, 'Понял', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (52, 27, 15, 'Отличная работа!', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (53, 28, 16, 'Благодарю!', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (54, 29, 17, 'Рад помочь', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (55, 30, 18, 'Всегда пожалуйста!', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (56, 1, 20, 'Как продвигается?', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (57, 2, 25, 'Нужна встреча', '2026-01-28 00:04:35.398111', 'read');
INSERT INTO public.messages VALUES (58, 3, 30, 'Привет!', '2026-01-28 00:04:35.398111', 'unread');
INSERT INTO public.messages VALUES (59, 4, 1, 'Спасибо!', '2026-01-28 00:04:35.398111', 'sent');
INSERT INTO public.messages VALUES (60, 5, 2, 'Все ок', '2026-01-28 00:04:35.398111', 'read');


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: alex
--

INSERT INTO public.users VALUES (27, 'anna_karenina', 'Anna', 'Karenina', 'anna.k@example.com', '2026-01-28 00:04:35.398111', 'blocked', '2026-01-28 00:07:11.59233', 'Blocking user via GUI');
INSERT INTO public.users VALUES (30, 'fedor_fedorich', 'Fedor', 'Fedorich', 'fedor.f@example.com', '2026-01-28 00:04:35.398111', 'deleted', '2026-01-28 00:08:48.749187', 'Deleting user via GUI');
INSERT INTO public.users VALUES (1, 'alex', 'Alexey', 'Vitiya', 'alex@mail.ru', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (2, 'vera', 'Vera', 'Novicova', 'Novicova@mail.ru', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (3, 'john_doe', 'John', 'Doe', 'john.doe@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (4, 'jane_smith', 'Jane', 'Smith', 'jane.smith@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (5, 'alex_wong', 'Alex', 'Wong', 'alex.wong@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (6, 'maria_garcia', 'Maria', 'Garcia', 'maria.garcia@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (7, 'robert_chen', 'Robert', 'Chen', 'robert.chen@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (8, 'sophia_kim', 'Sophia', 'Kim', 'sophia.kim@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (9, 'michael_brown', 'Michael', 'Brown', 'michael.brown@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (10, 'emily_davis', 'Emily', 'Davis', 'emily.davis@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (11, 'david_miller', 'David', 'Miller', 'david.miller@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (12, 'olivia_wilson', 'Olivia', 'Wilson', 'olivia.wilson@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (13, 'william_taylor', 'William', 'Taylor', 'william.taylor@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (14, 'ava_thomas', 'Ava', 'Thomas', 'ava.thomas@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (15, 'james_moore', 'James', 'Moore', 'james.moore@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (16, 'chloe_anderson', 'Chloe', 'Anderson', 'chloe.anderson@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (17, 'benjamin_jackson', 'Benjamin', 'Jackson', 'benjamin.jackson@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (18, 'lily_white', 'Lily', 'White', 'lily.white@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (19, 'samuel_harris', 'Samuel', 'Harris', 'samuel.harris@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (20, 'ella_martin', 'Ella', 'Martin', 'ella.martin@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (21, 'henry_thompson', 'Henry', 'Thompson', 'henry.thompson@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (22, 'grace_lee', 'Grace', 'Lee', 'grace.lee@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (23, 'vitec', NULL, NULL, NULL, '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (24, 'dodo', NULL, NULL, NULL, '2026-01-28 00:04:35.398111', 'blocked', NULL, NULL);
INSERT INTO public.users VALUES (25, 'lida', NULL, NULL, NULL, '2026-01-28 00:04:35.398111', 'deleted', NULL, NULL);
INSERT INTO public.users VALUES (28, 'boris_britva', 'Boris', 'Britva', 'boris.b@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (29, 'semen_semenich', 'Semen', 'Semenich', 'semen.s@example.com', '2026-01-28 00:04:35.398111', 'active', NULL, NULL);
INSERT INTO public.users VALUES (26, 'max_power', 'Max', 'Power', 'max.power@example.com', '2026-01-28 00:04:35.398111', 'blocked', '2026-01-28 00:07:01.964317', 'Blocking user via GUI');


--
-- Name: hashes hashes_pkey; Type: CONSTRAINT; Schema: public; Owner: alex
--

ALTER TABLE ONLY public.hashes
    ADD CONSTRAINT hashes_pkey PRIMARY KEY (id);


--
-- Name: messages messages_pkey; Type: CONSTRAINT; Schema: public; Owner: alex
--

ALTER TABLE ONLY public.messages
    ADD CONSTRAINT messages_pkey PRIMARY KEY (id);


--
-- Name: users unique_login_email; Type: CONSTRAINT; Schema: public; Owner: alex
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT unique_login_email UNIQUE (login, email);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: alex
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- Name: users add_user_to_hashes; Type: TRIGGER; Schema: public; Owner: alex
--

CREATE TRIGGER add_user_to_hashes AFTER INSERT ON public.users FOR EACH ROW EXECUTE PROCEDURE public.add_user_to_hash();


--
-- Name: hashes user_id_key; Type: FK CONSTRAINT; Schema: public; Owner: alex
--

ALTER TABLE ONLY public.hashes
    ADD CONSTRAINT user_id_key FOREIGN KEY (user_id) REFERENCES public.users(id) ON DELETE CASCADE;


--
-- PostgreSQL database dump complete
--

