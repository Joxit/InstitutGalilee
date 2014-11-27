CREATE SCHEMA DEVOIR;

CREATE TABLE DEVOIR.BUREAUX
(
	BUREAU_ID  INTEGER GENERATED ALWAYS AS IDENTITY NOT NULL,
	BATIMENT  CHAR CHECK (BATIMENT IN ('A', 'B')) NOT NULL,
	ETAGE     INTEGER CHECK (ETAGE IN (1, 2, 3)) NOT NULL,
	NUMERO    INTEGER CHECK (NUMERO > 0 AND NUMERO < 1000) NOT NULL,
	LIMITE    INTEGER NOT NULL,

	CONSTRAINT PK_BUREAUX PRIMARY KEY (BUREAU_ID),
    CONSTRAINT UK_AFFECT_BUREAU UNIQUE (BATIMENT, ETAGE, NUMERO)
);

CREATE TABLE DEVOIR.EQUIPES
(
	EQUIPE_ID VARCHAR(10) NOT NULL CHECK(EQUIPE_ID = UPPER(EQUIPE_ID)),

	CONSTRAINT PK_EQUIPES PRIMARY KEY (EQUIPE_ID)
);

CREATE TABLE DEVOIR.PERSONNES
(
	PERSONNE_ID INTEGER GENERATED ALWAYS AS IDENTITY NOT NULL,
	NOM         VARCHAR(25) NOT NULL,
	PRENOM      VARCHAR(25) NOT NULL,
	BUREAU      INTEGER,
	MAIL        VARCHAR(50) NOT NULL,
	EQUIPE      VARCHAR(10) NOT NULL,
    DEBUT       DATE NOT NULL,
    FIN         DATE,

	CONSTRAINT PK_PERSONNES PRIMARY KEY (PERSONNE_ID),
	CONSTRAINT FK_PERSONNES_BUREAU FOREIGN KEY (BUREAU) REFERENCES DEVOIR.BUREAUX(BUREAU_ID),
	CONSTRAINT FK_BUREAUX_EQUIPE FOREIGN KEY (EQUIPE) REFERENCES DEVOIR.EQUIPES(EQUIPE_ID)
);

CREATE TABLE DEVOIR.RESPONSABLES
(
	PERSONNE     INTEGER NOT NULL,
	IDENTIFIANT  VARCHAR(20) NOT NULL,
	MOT_DE_PASSE VARCHAR(20) NOT NULL,

	CONSTRAINT PK_RESPONSABLE PRIMARY KEY (IDENTIFIANT),
	CONSTRAINT FK_RESPONSABLE_PERSONNE FOREIGN KEY (PERSONNE) REFERENCES DEVOIR.PERSONNES(PERSONNE_ID)
);

CREATE TABLE DEVOIR.MESSAGES
(
	MESSAGE_ID   INTEGER GENERATED ALWAYS AS IDENTITY NOT NULL,
	MESSAGE      VARCHAR(2000) NOT NULL,
	ETAT         BOOLEAN NOT NULL DEFAULT FALSE,
	AUTEUR       INTEGER NOT NULL,
	ENVOIE       TIMESTAMP DEFAULT CURRENT TIMESTAMP,

	CONSTRAINT PK_MESSAGE PRIMARY KEY (MESSAGE_ID),
	CONSTRAINT FK_MESSAGE_AUTEUR FOREIGN KEY (AUTEUR) REFERENCES DEVOIR.PERSONNES(PERSONNE_ID)
);


