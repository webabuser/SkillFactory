-- phpMyAdmin SQL Dump
-- version 4.6.6deb5ubuntu0.5
-- https://www.phpmyadmin.net/
--
-- Хост: localhost:3306
-- Время создания: Янв 21 2025 г., 02:21
-- Версия сервера: 5.7.42-0ubuntu0.18.04.1
-- Версия PHP: 7.2.24-0ubuntu0.18.04.17

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: chat
--

-- --------------------------------------------------------

--
-- Структура таблицы hashes
--

CREATE TABLE hashes (
  id int(11) NOT NULL,
  user_id int(11) NOT NULL,
  hash char(40) COLLATE utf8_unicode_ci DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Хэши юзеров';

-- --------------------------------------------------------

--
-- Структура таблицы messages
--

CREATE TABLE messages (
  id int(11) NOT NULL,
  sender_id int(11) NOT NULL,
  receiver_id int(11) NOT NULL,
  text text COLLATE utf8_unicode_ci,
  created timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  status set('sent','read','unread','deleted','received') COLLATE utf8_unicode_ci NOT NULL DEFAULT 'unread'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='Таблица комментариев';

-- --------------------------------------------------------

--
-- Структура таблицы users
--

CREATE TABLE users (
  id int(11) NOT NULL,
  login varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  name varchar(100) COLLATE utf8_unicode_ci DEFAULT NULL,
  surname varchar(100) COLLATE utf8_unicode_ci DEFAULT NULL,
  email varchar(100) COLLATE utf8_unicode_ci DEFAULT NULL,
  created timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Триггеры users
--
DELIMITER $$
CREATE TRIGGER `user_id_to_hash` AFTER INSERT ON `users` FOR EACH ROW INSERT INTO hashes (user_id, hash) VALUES (NEW.id, NULL)
$$
DELIMITER ;

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы hashes
--
ALTER TABLE hashes
  ADD PRIMARY KEY (id),
  ADD KEY user_id (user_id);

--
-- Индексы таблицы messages
--
ALTER TABLE messages
  ADD PRIMARY KEY (id),
  ADD KEY sender_id (sender_id),
  ADD KEY receiver_id (receiver_id);

--
-- Индексы таблицы users
--
ALTER TABLE users
  ADD PRIMARY KEY (id),
  ADD UNIQUE KEY login (login),
  ADD UNIQUE KEY email (email);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы hashes
--
--ALTER TABLE hashes
--  MODIFY id int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT для таблицы messages
--
--ALTER TABLE messages
--  MODIFY id int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT для таблицы users
--
--ALTER TABLE users
--  MODIFY id int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы hashes
--
ALTER TABLE hashes
  ADD CONSTRAINT hashes_ibfk_1 FOREIGN KEY (user_id) REFERENCES `users` (id) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
