-- Database: hw1

--hw1
-- Victor gavrilenko 209406255
--Ilay cohen 206515744


CREATE TABLE Project (
	pid INTEGER PRIMARY KEY,
	pname VARCHAR(50) NOT NULL,
	address VARCHAR(50),
	city VARCHAR(50) NOT NULL,
	ptype VARCHAR(50) DEFAULT 'infrastructures' CHECK (ptype IN ('residence','industry','infrastructures'))
);

CREATE TABLE Materials (
	mname VARCHAR(50) UNIQUE,
	manufacturer VARCHAR(15) UNIQUE,
	description VARCHAR(50) NOT NULL,
	price INTEGER DEFAULT 0 CHECK (price >=0),
	feature VARCHAR(30) UNIQUE,
	CONSTRAINT pm_key PRIMARY KEY (mname, manufacturer)
);

CREATE TABLE Inspector (
	iid INTEGER PRIMARY KEY UNIQUE CHECK ((iid > 0) AND (iid IS NOT NULL)),
	iname VARCHAR(20) NOT NULL,
	bdate TIMESTAMP NOT NULL,
	teducation VARCHAR(30) CHECK (teducation IN ('practical', 'engineer')),
	sdate TIMESTAMP NOT NULL,
	mobile VARCHAR(11) UNIQUE NOT NULL CHECK (mobile LIKE ('05%')),
	years FLOAT NOT NULL,
	CONSTRAINT ch_dd CHECK (sdate > bdate),
	CONSTRAINT ch_y3 CHECK (years >= 3)
);

CREATE TABLE ProjectMaterials (
	pid INTEGER,
	mname VARCHAR(50),
	manufacturer VARCHAR(30),
	sdate TIMESTAMP NOT NULL,
	amount INTEGER CHECK (amount >= 1),

	FOREIGN KEY (pid) REFERENCES Project(pid) ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY (mname) REFERENCES Materials(mname)  ON UPDATE CASCADE ON DELETE NO ACTION,
	FOREIGN KEY (manufacturer) REFERENCES Materials(manufacturer) ON UPDATE CASCADE ON DELETE NO ACTION,
	CONSTRAINT tab_pk1 PRIMARY KEY (pid, mname, manufacturer)
);

CREATE TABLE Inspection (
	pid INTEGER,
	idate TIMESTAMP NOT NULL,
	iid INTEGER,
	stime TIMESTAMP NOT NULL,
	status INTEGER CHECK (status IN (0, 1, 2)),
	FOREIGN KEY (pid) REFERENCES Project(pid) ON UPDATE CASCADE ON DELETE CASCADE,
	FOREIGN KEY (iid) REFERENCES Inspector(iid) ON UPDATE CASCADE ON DELETE NO ACTION,
	CONSTRAINT tab_pk2 PRIMARY KEY (pid, idate),
	CONSTRAINT ch_dt CHECK (idate > stime)
);
