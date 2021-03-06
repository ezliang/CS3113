#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include "SheetSprite.h"
#include "ShaderProgram.h"
#include "config.h"

SheetSprite::SheetSprite(unsigned int textureID, float x_res, float y_res, int sheet_x, int sheet_y, float padding, int index, float w, float h, float size) :
	textureID(textureID),
	x_res(x_res),
	y_res(y_res),
	size(size),
	width(w/x_res),
	height(h/y_res),
	org_width(w),
	org_height(h),
	sheet_x(sheet_x),
	sheet_y(sheet_y),
	padding(padding)
{
	this->u = ((float)(((int)index) % sheet_x) * (width+padding) + padding) / x_res;
	this->v = (floor((float)(((int)index) / sheet_y)) * (width + padding) + padding) / y_res;
}


void SheetSprite::Draw(ShaderProgram* program){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, textureID);

		GLfloat texCoords[] = {
			u, v + height,
			u + width, v,
			u, v,
			u + width, v,
			u, v + height,
			u + width, v + height
		};

		float aspect = width / height;

		float vertices[] = {
			-0.5f * size * aspect, -0.5 * size,
			0.5f * size * aspect, 0.5f * size,
			-0.5f * size * aspect, 0.5f * size,
			0.5f * size * aspect, 0.5f * size,
			-0.5f * size * aspect, -0.5f * size,
			0.5f * size * aspect, -0.5f * size
		};

		glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
		glEnableVertexAttribArray(program->positionAttribute);

		glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
		glEnableVertexAttribArray(program->texCoordAttribute);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(program->positionAttribute);
		glDisableVertexAttribArray(program->texCoordAttribute);
		glDisable(GL_BLEND);
}