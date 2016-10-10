
/*
-- Script creacion de tablas ICTAC 2015 
-- By Carlos Motta
------------------------------------------------------------
------------------------------------------------------------
-- Tabla cliente
*/

CREATE TABLE Persona
(
  id_persona        INTEGER NOT NULL AUTO_INCREMENT,
  id_evento         INTEGER,
  nombre            VARCHAR(15),
  apellido          VARCHAR(15),
  edad  	          INTEGER,
  documento         VARCHAR(80),
  tipoDoc           VARCHAR(12),
  Organizador       INTEGER,
  Asistente         INTEGER,
  Autor             INTEGER,
  PRIMARY KEY (id_persona)
)


 ALTER TABLE Persona ADD 
  CONSTRAINT id_persona_pk
 PRIMARY KEY
 (id_persona);


/*
------------------------------------------------------------
------------------------------------------------------------
-- Tabla Evento
*/

CREATE TABLE Evento
(
  id_evento         INTEGER NOT NULL AUTO_INCREMENT,
  nombre            VARCHAR(80),  
  direccion_lugar   VARCHAR(80),
  descripcion       VARCHAR(150),
  PRIMARY KEY (id_evento)
)

ALTER TABLE Evento ADD 
  CONSTRAINT id_evento_pk
 PRIMARY KEY
 (id_evento);

/*
------------------------------------------------------------
------------------------------------------------------------
-- Tabla Actividad
*/

CREATE TABLE Actividad
(
  id_actividad      INTEGER NOT NULL AUTO_INCREMENT,
  id_evento       	INTEGER,
  nombre            VARCHAR(15),
  descripcion       VARCHAR(150),
  PRIMARY KEY (id_actividad)
)

ALTER TABLE Actividad ADD 
  CONSTRAINT id_actividad_pk
 PRIMARY KEY
 (id_actividad);

  ALTER TABLE Actividad ADD 
  CONSTRAINT id_evento_fk
 FOREIGN KEY (id_evento) REFERENCES Evento(id_evento);

/*
------------------------------------------------------------
------------------------------------------------------------
-- Tabla Persona X Actividad
*/

CREATE TABLE Persona_x_Actividad
(
  id_PxA            INTEGER AUTO_INCREMENT,
  id_persona        INTEGER,
  id_actividad      INTEGER,
  Rol               VARCHAR(2),
  descargado        INTEGER
  PRIMARY KEY (id_PxA)
 )

ALTER TABLE Persona_x_Actividad ADD 
  CONSTRAINT id_PxA_pk
 PRIMARY KEY
 (id_PxA);

  ALTER TABLE Persona_x_Actividad ADD 
  CONSTRAINT id_persona_fk
 FOREIGN KEY (id_persona) REFERENCES Persona(id_persona);

   ALTER TABLE Persona_x_Actividad ADD 
  CONSTRAINT id_actividad_fk
 FOREIGN KEY (id_actividad) REFERENCES Actividad(id_actividad);

