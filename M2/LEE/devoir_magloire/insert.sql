INSERT INTO EQUIPES(EQUIPE_ID) VALUES ('A3');
INSERT INTO EQUIPES(EQUIPE_ID) VALUES ('AOC');
INSERT INTO EQUIPES(EQUIPE_ID) VALUES ('CALIN');
INSERT INTO EQUIPES(EQUIPE_ID) VALUES ('LCR');
INSERT INTO EQUIPES(EQUIPE_ID) VALUES ('RCLN');

INSERT INTO BUREAUX(BATIMENT, ETAGE, NUMERO, LIMITE) VALUES ('A', 1, 103, 4);
INSERT INTO BUREAUX(BATIMENT, ETAGE, NUMERO, LIMITE) VALUES ('B', 1, 103, 10);

INSERT INTO PERSONNES(NOM, PRENOM, BUREAU, MAIL, EQUIPE) VALUES ( 'Magloire', 'Jones', 1, 'magloire@lipn.fr', 'CALIN');

INSERT INTO RESPONSABLES(PERSONNE, IDENTIFIANT, MOT_DE_PASSE) VALUES (1, 'joxit', 'mdp');
