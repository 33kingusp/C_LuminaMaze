#Makefile
game: main.o input.o control.o database.o random.o maze.o vector.o pixel.o graphics.o sprite.o object.o layer.o stage.o update.o canvas.o enemy.o
	(cd ./librarys/; cc ../main.o ./input/*.o ./control/*.o ./database/*.o ./random/*.o ./maze/*.o ./vector/*.o ./pixel/*.o ./graphics/*.o ./sprite/*.o ./object/*.o ./layer/*.o ./stage/*.o ./update/*.o ./canvas/*.o ./enemy/*.o -lm -lncurses -o ../game)

#--------------------
main.o: main.c

#入力
input.o:
	(cd ./librarys/input/; make)

control.o:
	(cd ./librarys/control/; make)

#データ
database.o:
	(cd ./librarys/database/; make)

#乱数
random.o:
	(cd ./librarys/random/; make)

#迷路生成
maze.o:
	(cd ./librarys/maze/; make)

#画像系
vector.o:
	(cd ./librarys/vector/; make)

pixel.o:
	(cd ./librarys/pixel/; make)

graphics.o:
	(cd ./librarys/graphics/; make)

sprite.o:
	(cd ./librarys/sprite/; make)

object.o:
	(cd ./librarys/object/; make)

layer.o:
	(cd ./librarys/layer/; make)

update.o:
	(cd ./librarys/update/; make)

stage.o:
	(cd ./librarys/stage/; make)

canvas.o:
	(cd ./librarys/canvas/; make)
#敵
enemy.o:
	(cd ./librarys/enemy/; make)

#--------------------
.c.o:
	cc -c $< -Wall

.PHONY: clean

clean:
	(find ./librarys -type f -name *.o -exec rm {} +; rm main.o; rm game)
