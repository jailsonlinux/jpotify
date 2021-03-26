
CREATE TABLE IF NOT EXISTS "users" (
	"id"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"nome"	TEXT UNIQUE,
	"clientid"	TEXT UNIQUE,
	"secret"	TEXT,
	"access_token"	TEXT,
	"autologin"	INTEGER DEFAULT 0
);

CREATE TABLE  IF NOT EXISTS "playlists" (
	"id"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"userid"	INTEGER NOT NULL,
	"nome"	TEXT NOT NULL,
	"descricao"	TEXT,
	"apiid"	TEXT
);

CREATE TABLE  IF NOT EXISTS "musicas" (
	"key"	TEXT,
	"playlistid"	INTEGER,
	"nome"	TEXT,
	"artista"	TEXT,
	"album"	TEXT,
	"duracao"	INTEGER,
	"ordem"	INTEGER,
	"track" TEXT,
	"previewUrl" TEXT,
	"imagem" TEXT,
	PRIMARY KEY("key","playlistid")
);

DELETE FROM myitems WHERE orderindex=6;    
UPDATE myitems SET orderindex = (orderindex - 1) WHERE orderindex > 6;
To swap two items (4 and 7):

UPDATE myitems SET orderindex = 0 WHERE orderindex = 4;
UPDATE myitems SET orderindex = 4 WHERE orderindex = 7;
UPDATE myitems SET orderindex = 7 WHERE orderindex = 0;
i.e. 0 is not used, so use a it as a dummy to avoid having an ambiguous item.

To insert at 3:

 UPDATE myitems SET orderindex = (orderindex + 1) WHERE orderindex > 2;
 INSERT INTO myitems (Myitem,orderindex) values ("MytxtitemHere",3)
