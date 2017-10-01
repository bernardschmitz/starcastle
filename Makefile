
# $Id: Makefile,v 1.3 2004-06-24 01:01:42 bernard Exp $

ifdef OPTIMIZE
	CFLAGS=-DNDEBUG -Wall -O3 -fomit-frame-pointer -ffast-math -funroll-loops
	LFLAGS=-L/home/bernard/cross/cross-tools/lib -s
else
	ifdef PROFILE
		CFLAGS=-Wall -pg -O2 -ffast-math
		LFLAGS=-L/home/bernard/cross/cross-tools/lib -pg
	else
		CFLAGS=-Wall -g
		LFLAGS=-L/home/bernard/cross/cross-tools/lib -g
	endif
endif

#LIB=`allegro-config --libs release` -lm
LIB=-lalleg -lm
CC=g++
LD=g++
AR=

.cc.o:
	$(CC) -c $(CFLAGS) $*.cc

SRC = actor.cc console.cc init.cc player.cc input.cc vector.cc \
      trig.cc matrix.cc memory.cc shot.cc exp.cc random.cc shock.cc \
      castle.cc laser.cc bomb.cc outer.cc middle.cc inner.cc sparks.cc \
      score.cc param.cc message.cc title.cc

OBJ = actor.o console.o init.o player.o input.o vector.o trig.o \
      matrix.o memory.o shot.o exp.o random.o shock.o castle.o \
      laser.o bomb.o outer.o middle.o inner.o sparks.o score.o \
      param.o message.o title.o

star.exe:	$(OBJ) main.o 
	$(LD) $(OBJ) main.o -o star.exe $(LFLAGS) -s $(LIB)

clean:
	rm *.o star.exe

##

actor.o: actor.cc actor.h init.h
bomb.o: bomb.cc vector.h matrix.h trig.h param.h bomb.h init.h actor.h \
 player.h exp.h random.h
castle.o: castle.cc castle.h init.h actor.h vector.h matrix.h trig.h \
 param.h bomb.h laser.h shock.h exp.h random.h player.h outer.h \
 middle.h inner.h score.h
console.o: console.cc init.h console.h
exp.o: exp.cc vector.h matrix.h trig.h param.h exp.h init.h actor.h \
 random.h sparks.h
init.o: init.cc init.h console.h param.h data.h
inner.o: inner.cc vector.h matrix.h trig.h param.h exp.h init.h \
 actor.h random.h inner.h score.h
input.o: input.cc input.h
laser.o: laser.cc laser.h init.h actor.h vector.h matrix.h trig.h \
 param.h player.h bomb.h
main.o: main.cc init.h player.h actor.h vector.h input.h shot.h \
 param.h exp.h random.h shock.h castle.h laser.h bomb.h outer.h \
 middle.h inner.h sparks.h score.h
makegrid.o: makegrid.cc
matrix.o: matrix.cc vector.h matrix.h trig.h
memory.o: memory.cc
middle.o: middle.cc vector.h matrix.h trig.h param.h exp.h init.h \
 actor.h random.h middle.h score.h
outer.o: outer.cc vector.h matrix.h trig.h param.h exp.h init.h \
 actor.h random.h outer.h middle.h inner.h score.h
player.o: player.cc player.h init.h actor.h vector.h input.h matrix.h \
 trig.h param.h shot.h shock.h exp.h random.h score.h
random.o: random.cc random.h
score.o: score.cc param.h score.h actor.h init.h
shock.o: shock.cc vector.h matrix.h trig.h param.h shock.h init.h \
 actor.h
shot.o: shot.cc vector.h matrix.h trig.h param.h shot.h init.h actor.h \
 exp.h random.h score.h
sparks.o: sparks.cc init.h sparks.h actor.h vector.h param.h random.h \
 trig.h
test.o: test.cc data.h
trig.o: trig.cc trig.h
vector.o: vector.cc vector.h
param.o: param.cc param.h
message.o: message.cc message.h
title.o: title.cc init.h input.h random.h shock.h actor.h vector.h \
 param.h bomb.h sparks.h
