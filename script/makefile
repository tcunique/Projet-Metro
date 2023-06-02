# Définir le compilateur C
CC = gcc

# Définir les options du compilateur C
CFLAGS = -Wall

# Définir les fichiers sources .c et les ficiers objets .o
SRCS = $(wildcard *.c) #Permet de générer la liste des fichiers .c
OBJS = $(SRCS:.c=.o) #Permet de générer la liste des fichiers .o

# Nom du fichier executable 
EXEC = test

# Règle all qui compile le programme
all: $(EXEC)

# Règle pour compiler l'exécutable
$(EXEC): $(OBJS)
	$(CC) -o $@ $^

# Règle de compilation des fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle clean qui supprime les fichiers objets
clean:
	rm -f $(OBJS) $(EXEC)

# Dépendances
main.o: main.c liste.h truc.h abr.h ligne.h
truc.o: truc.c truc.h coord.h connexion.h station.h 
liste.o: liste.c liste.h truc.h
coord.o: coord.c coord.h
abr.o: abr.c abr.h truc.h liste.h
ligne.o: ligne.c ligne.h truc.h
