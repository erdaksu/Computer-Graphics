#pragma once
bool keysStateArray[127];
bool specialKeysStateArray[127];

void renderSpacedBitmapString(float x, float y, void *font, char *string) {
	char *c;
	int x1 = x;
	for (c = string; *c != '\0'; c++) {
		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font, *c);
	}
}
void circle1(double radius, double xc, double yc)
{
	int i;
	double angle = 2 * 3.1415 / 20;	// circle is drawn using 20 line.
	double x = 0, y = 0;

	glBegin(GL_LINE_LOOP);

	for (i = 0; i<20; i++)
	{
		x = radius * cos(i *angle) + xc;
		y = radius * sin(i * angle) + yc;
		glVertex2f(x, y);
	}
	glEnd();
}
void drawBoundingCircle1(Sprite theSprite)
{
	glLoadIdentity();
	circle1(theSprite.colRadius, theSprite.colx, theSprite.coly);
}

void drawBoundingBox(Sprite theSprite)
{
	float tmpx, tmpy;
	glLoadIdentity();
	tmpx = theSprite.colWidth / 2.0;
	tmpy = theSprite.colHeight / 2.0;
	glColor3f(theSprite.r, theSprite.g, theSprite.b);
	glBegin(GL_LINE_LOOP);
	glVertex2f(theSprite.colx - tmpx, theSprite.coly - tmpy);
	glVertex2f(theSprite.colx + tmpx, theSprite.coly - tmpy);
	glVertex2f(theSprite.colx + tmpx, theSprite.coly + tmpy);
	glVertex2f(theSprite.colx - tmpx, theSprite.coly + tmpy);
	glEnd();
	glColor3f(1, 1, 1);
}
void initSpriteTexture(char str[], int *tex)
{
	*tex = SOIL_load_OGL_texture(str, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}


void drawBackgroundSprite(Sprite theSprite)
{
	glColor4f(1, 1, 1, 1);
	glEnable(GL_TEXTURE_2D); //
	glBindTexture(GL_TEXTURE_2D, theSprite.textureIndex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(theSprite.x, theSprite.y);
	glTexCoord2d(1.0, 0.0); glVertex2d(theSprite.width + theSprite.x, theSprite.y);
	glTexCoord2d(1.0, 1.0); glVertex2d(theSprite.width + theSprite.x, theSprite.height + theSprite.y);
	glTexCoord2d(0.0, 1.0); glVertex2d(theSprite.x, theSprite.height + theSprite.y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawCharacterSprite(Sprite theSprite)
{
	glColor4f(1, 1, 1, 1);
	glEnable(GL_TEXTURE_2D); //
	glBindTexture(GL_TEXTURE_2D, theSprite.textureIndex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(theSprite.x, theSprite.y);
	glTexCoord2d(1.0, 0.0); glVertex2d(theSprite.width + theSprite.x, theSprite.y);
	glTexCoord2d(1.0, 1.0); glVertex2d(theSprite.width + theSprite.x, theSprite.height + theSprite.y);
	glTexCoord2d(0.0, 1.0); glVertex2d(theSprite.x, theSprite.height + theSprite.y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawCharacterSprite1(Sprite theSprite)
{
	glColor4f(1, 1, 1, 1);
	glEnable(GL_TEXTURE_2D); //
	glBindTexture(GL_TEXTURE_2D, theSprite.textureIndex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(theSprite.x, theSprite.y);
	glTexCoord2d(1.0, 0.0); glVertex2d(theSprite.width + theSprite.x, theSprite.y);
	glTexCoord2d(1.0, 1.0); glVertex2d(theSprite.width + theSprite.x, theSprite.height + theSprite.y);
	glTexCoord2d(0.0, 1.0); glVertex2d(theSprite.x, theSprite.height + theSprite.y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void drawSpriteFromSheet(Sprite theSprite, int index)
{
	float dx = theSprite.animSheetDx; float dy = theSprite.animSheetDy;

	glEnable(GL_TEXTURE_2D); //
	glBindTexture(GL_TEXTURE_2D, theSprite.textureIndex);
	glColor4f(theSprite.r, theSprite.g, theSprite.b, theSprite.a);
	glBegin(GL_QUADS);
	glTexCoord2d(theSprite.imageOffsetList[index].x, theSprite.imageOffsetList[index].y);			glVertex2d(-theSprite.width / 2, -theSprite.height / 2);
	glTexCoord2d(theSprite.imageOffsetList[index].x + dx, theSprite.imageOffsetList[index].y);		glVertex2d(theSprite.width / 2, -theSprite.height / 2);
	glTexCoord2d(theSprite.imageOffsetList[index].x + dx, theSprite.imageOffsetList[index].y + dy);	glVertex2d(theSprite.width / 2, theSprite.height / 2);
	glTexCoord2d(theSprite.imageOffsetList[index].x, theSprite.imageOffsetList[index].y + dy);		glVertex2d(-theSprite.width / 2, theSprite.height / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);
	if (drawBoundingBoxes) drawBoundingBox(theSprite);
	if (drawBoundingCircles)drawBoundingCircle1(theSprite);
}
void drawSprite(Sprite theSprite)
{
	glEnable(GL_TEXTURE_2D); //
	glBindTexture(GL_TEXTURE_2D, theSprite.textureIndex);
	glColor4f(theSprite.r, theSprite.g, theSprite.b, theSprite.a);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(-theSprite.width / 2, -theSprite.height / 2);
	glTexCoord2d(1.0, 0.0); glVertex2d(theSprite.width / 2, -theSprite.height / 2);
	glTexCoord2d(1.0, 1.0); glVertex2d(theSprite.width / 2, theSprite.height / 2);
	glTexCoord2d(0.0, 1.0); glVertex2d(-theSprite.width / 2, theSprite.height / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor4f(1,1,1,1);
	if (drawBoundingBoxes) drawBoundingBox(theSprite);
	if (drawBoundingCircles)drawBoundingCircle1(theSprite);
}

void translateCollider(Sprite *theSprite, float tx, float ty)
{
	theSprite->colx = tx;
	theSprite->coly = ty;
}
void rotateCollider(Sprite *theSprite, float angle)
{
	double dtor = 3.14159265358979323846 / 180.0; //convert degrees to radians

	float rotatedx = (theSprite->colx * cos(angle*dtor)) - (theSprite->coly * sin(angle*dtor));
	float rotatedy = (theSprite->colx * sin(angle*dtor)) + (theSprite->coly * cos(angle*dtor));
	theSprite->colx = rotatedx;
	theSprite->coly = rotatedy;
}

void scaleCollider(Sprite *theSprite, float sx, float sy) {
	theSprite->colWidth = theSprite->colStartWidth*sx;
	theSprite->colHeight = theSprite->colStartHeight*sy;
	theSprite->colRadius = theSprite->colStartRadius *sx;
}
void rotateVector(Sprite *theSprite)
{
	double dtor = 3.14159265358979323846 / 180.0; //convert degrees to radians

	float rotatedx = (theSprite->startVectorX * cos(theSprite->rz*dtor)) - (theSprite->startVectorY * sin(theSprite->rz*dtor));
	float rotatedy = (theSprite->startVectorX * sin(theSprite->rz*dtor)) + (theSprite->startVectorY * cos(theSprite->rz*dtor));
	theSprite->forwardVectorX = rotatedx; theSprite->forwardVectorY = rotatedy;
	theSprite->backVectorX = -rotatedx; theSprite->backVectorY = -rotatedy;
	rotatedy = (theSprite->forwardVectorX * sin(-90.0*dtor)) + (theSprite->forwardVectorY * cos(-90.0*dtor));
	rotatedx = (theSprite->forwardVectorX * cos(-90.0*dtor)) - (theSprite->forwardVectorY * sin(-90.0*dtor));
	theSprite->rightVectorX = rotatedx; theSprite->rightVectorY = rotatedy;
	theSprite->leftVectorX = -rotatedx; theSprite->leftVectorY = -rotatedy;
}
bool collisionDetectRects(Sprite *first, Sprite *second)
{
	if ((first->colx - (first->colWidth / 2.0) < (second->colx - (second->colWidth / 2.0) + second->colWidth)) &&
		(first->colx - (first->colWidth / 2.0) + first->colWidth > second->colx - (second->colWidth / 2.0)) &&
		(first->coly - (first->colHeight / 2.0) < (second->coly - (second->colHeight / 2.0) + second->colHeight)) &&
		(first->coly - (first->colHeight / 2.0) + first->colHeight > second->coly - (second->colHeight / 2.0))) {
		return true;
	}
	else
	{
		return false;
	}
}
bool collisionDetectCircles(Sprite *first, Sprite *second)
{
	float dist = first->colRadius + second->colRadius;
	float xdist = first->tx - second->tx;
	float ydist = first->ty- second->ty;
	float d = dist * dist;
	float x = xdist * xdist;
	float y = ydist * ydist;
	if ((dist*dist)>((xdist*xdist)+(ydist*ydist)))
		return true;
	else
	{
		return false;
	}
}


void initSprite(Sprite *theSprite, int texture, int tx, int ty, int width, int height)
{
	theSprite->textureIndex = texture;
	theSprite->width = width;
	theSprite->height = height;
	theSprite->colStartWidth = width;
	theSprite->colStartHeight = height;
	theSprite->colWidth = width;
	theSprite->colHeight = height;
	theSprite->colRadius = (width + height) / 4.0;
	theSprite->colStartRadius = theSprite->colRadius;
	theSprite->tx = tx;
	theSprite->ty = ty;

}
void wrapSprite(Sprite *theSprite)
{
	if (theSprite->tx > winWidth)theSprite->tx = 0; if (theSprite->tx < 0)theSprite->tx = winWidth;
	if (theSprite->ty > winHeight)theSprite->ty = 0; if (theSprite->ty < 0)theSprite->ty = winHeight;
}
void goForward(Sprite *theSprite) {
	theSprite->tx += theSprite->forwardVectorX*theSprite->speed;
	theSprite->ty += theSprite->forwardVectorY*theSprite->speed;
}
void goBack(Sprite *theSprite) {
	theSprite->tx += theSprite->backVectorX*theSprite->speed;
	theSprite->ty += theSprite->backVectorY*theSprite->speed;
}
void goRight(Sprite *theSprite) {
	theSprite->tx += theSprite->rightVectorX*theSprite->speed;
	theSprite->ty += theSprite->rightVectorY*theSprite->speed;
}
void goLeft(Sprite *theSprite) {
	theSprite->tx += theSprite->leftVectorX*theSprite->speed;
	theSprite->ty += theSprite->leftVectorY*theSprite->speed;
}

float speed = 5;
void scrollBackground(Sprite *back1, Sprite *back2, float speed, int direction) {

	if (direction == 0) {
		if (back1->x == 0)back2->x = winWidth;
		drawBackgroundSprite(*back1);
		drawBackgroundSprite(*back2);
		back1->x -= speed;
		back2->x -= speed;
		if (back1->x <= -winWidth) {
			back1->x = 0;
			back2->x = winWidth;
		}
	}
	else 	if (direction == 1) {
		if (back1->x == 0)back2->x = -winWidth;
		drawBackgroundSprite(*back1);
		drawBackgroundSprite(*back2);
		back1->x += speed;
		back2->x += speed;
		if (back1->x >= winWidth) {
			back1->x = 0;
			back2->x = -winWidth;
		}
	}
	else 	if (direction == 2) {
		if (back1->y == 0)back2->y = -winHeight;
		drawBackgroundSprite(*back1);
		drawBackgroundSprite(*back2);
		back1->y += speed;
		back2->y += speed;
		if (back1->y >= winHeight) {
			back1->y = 0;
			back2->y = -winHeight;
		}
	}
	else 	if (direction == 3) {
		if (back1->y == 0)back2->y = winHeight;
		drawBackgroundSprite(*back1);
		drawBackgroundSprite(*back2);
		back1->y -= speed;
		back2->y -= speed;
		if (back1->y <= -winHeight) {
			back1->y = 0;
			back2->y = winHeight;
		}
	}
}

void specialKey(int k, int x, int y)
{
	if (k == KEY_LEFT)
		specialKeysStateArray[KEY_LEFT] = true;
	if (k == KEY_UP)
		specialKeysStateArray[KEY_UP] = true;
	if (k == KEY_RIGHT)
		specialKeysStateArray[KEY_RIGHT] = true;
	if (k == KEY_DOWN)
		specialKeysStateArray[KEY_DOWN] = true;
}
void specialKeyUp(int k, int x, int y)
{
	if (k == KEY_LEFT)
		specialKeysStateArray[KEY_LEFT] = false;
	if (k == KEY_UP)
		specialKeysStateArray[KEY_UP] = false;
	if (k == KEY_RIGHT)
		specialKeysStateArray[KEY_RIGHT] = false;
	if (k == KEY_DOWN)
		specialKeysStateArray[KEY_DOWN] = false;
}

void key(unsigned char k, int x, int y)
{
	if (k == 'a')
		keysStateArray[int('a')] = true;
	if (k == 'c')
		keysStateArray[int('c')] = true;
	if (k == 'd')
		keysStateArray[int('d')] = true;
	if (k == 'm')
		keysStateArray[int('m')] = true;
	if (k == 'q')
		keysStateArray[int('q')] = true;
	if (k == 's')
		keysStateArray[int('s')] = true;
	if (k == 't')
		keysStateArray[int('t')] = true;
	if (k == 'w')
		keysStateArray[int('w')] = true;
	if (k == 'z')
		keysStateArray[int('z')] = true;
}
void keyUp(unsigned char k, int x, int y)
{
	if (k == 'a')
		keysStateArray['a'] = false;
	if (k == 'c')
		keysStateArray['c'] = false;
	if (k == 'd')
		keysStateArray['d'] = false;
	if (k == 'm')
		keysStateArray['m'] = false;
	if (k == 'q')
		keysStateArray['q'] = false;
	if (k == 's')
		keysStateArray['s'] = false;
	if (k == 't')
		keysStateArray['t'] = false;
	if (k == 'w')
		keysStateArray['w'] = false;
	if (k == 'z')
		keysStateArray['z'] = false;

}
void CalculateFrameRate()
{
	static float framesPerSecond = 0.0f;       // This will store our fps
	static float lastTime = 0.0f;       // This will hold the time from the last frame
	float currentTime = GetTickCount() * 0.001f;
	++framesPerSecond;
	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;
		if (true == 1) fprintf(stderr, "\nCurrent Frames Per Second: %d\n\n", (int)framesPerSecond);
		framesPerSecond = 0;
	}
}
void initialiseSpriteFromSpriteSheet(Sprite *theSprite, int numSprites, float sheetWidth, float sheetHeight, float spriteWidth, float spriteHeight)
{
	int cols = sheetWidth / spriteWidth;
	int rows = sheetHeight / spriteHeight;
	theSprite->animSheetDx = spriteWidth / sheetWidth;
	theSprite->animSheetDy = spriteHeight / sheetHeight;
	theSprite->numAnimFrames = numSprites;
	float x = 0, y = 0;
	int count = 0;
	Point p;

	for (int i = rows - 1; i > -1; i--) {
		for (int j = 0; j < cols; j++) {

			x = j * spriteWidth;
			y = i * spriteHeight;
			p.x = x / sheetWidth; p.y = y / sheetHeight;
			theSprite->imageOffsetList.push_back(p);
			count++;
		}
	}
}