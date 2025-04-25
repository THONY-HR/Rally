CREATE DATABASE rallye;
USE rallye;

CREATE TABLE special (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom_special VARCHAR(50)
);

CREATE TABLE groupe (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom_groupe VARCHAR(50)
);

CREATE TABLE concurrent (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom_concurrent VARCHAR(50)
);

CREATE TABLE rallye (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_special INT,
    id_concurrent INT,
    id_groupe INT,
    FOREIGN KEY (id_special) REFERENCES special(id),
    FOREIGN KEY (id_concurrent) REFERENCES concurrent(id),
    FOREIGN KEY (id_groupe) REFERENCES groupe(id)
);

CREATE TABLE temps (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_special INT,
    id_concurrent INT,
    temps TIME,
    FOREIGN KEY (id_special) REFERENCES special(id),
    FOREIGN KEY (id_concurrent) REFERENCES concurrent(id)
);

CREATE VIEW details_participation AS
SELECT r.id AS rallye_id, c.nom_concurrent, s.nom_special, g.nom_groupe, t.temps
FROM rallye r
JOIN concurrent c ON r.id_concurrent = c.id
JOIN special s ON r.id_special = s.id
JOIN groupe g ON r.id_groupe = g.id
JOIN temps t ON r.id = t.id_special AND r.id_concurrent = t.id_concurrent;

INSERT INTO special (nom_special) VALUES
('Special 1'),
('Special 2'),
('Special 3');

INSERT INTO groupe (nom_groupe) VALUES
('Groupe A'),
('Groupe B'),
('Groupe C');

INSERT INTO concurrent (nom_concurrent) VALUES
('Concurrent 1'),
('Concurrent 2'),
('Concurrent 3');

INSERT INTO rallye (id_special, id_concurrent, id_groupe) VALUES
(1, 1, 1),
(2, 2, 2),
(3, 3, 3);

INSERT INTO temps (id_special, id_concurrent, temps) VALUES
(1, 1, '00:00:39'), 
(1, 2, '00:01:23'),  
(1, 3, '00:02:15'),  
(2, 1, '00:00:45'),  
(2, 2, '00:01:30'),  
(2, 3, '00:02:05'),  
(3, 1, '00:00:55'),  
(3, 2, '00:01:40'),  
(3, 3, '00:02:20');

SELECT * FROM details_participation ORDER BY nom_groupe;

SELECT * 
FROM details_participation 
ORDER BY temps = (SELECT MAX(temps) FROM details_participation), temps ASC;

SELECT *
FROM details_participation
ORDER BY nom_groupe,
         CASE WHEN temps = (SELECT MAX(temps) FROM details_participation) THEN 0 ELSE 1 END,
         temps ASC;

select sum(temps) from details_participation;
