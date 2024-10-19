#include <string>
  
#include "GL_ErrorHandeling.h"

struct HexaString
{
	std::string shortFormat;
	std::string longFormat;
};

void GL_ClearAllErrors(void)
{
	/* This is a fail safe, if someone forgets to use our error handeling with an opengl call and does use it on a following opengl call.
	   In that case there could have been generated some errors from that opengl call without the error handeling wich aren't cleared.
	   This can result in wrong errors at that point.
	   An error can be cleared by actually retreiving the error value. Clear all the messages by going through them with a loop */
	while (glGetError() != GL_NO_ERROR);
}

void DecToHexa(GLenum errorCode, HexaString& storeHexValue)
{
	/*Convert the Decimal opengl error code to hexadecimal*/
	int remainder = 0;

	while (errorCode != 0) {
		remainder = errorCode % 16;
		char ch;
		if (remainder >= 10)
			ch = remainder + 55;
		else
			ch = remainder + 48;
		storeHexValue.shortFormat += ch;
		storeHexValue.longFormat += ch;

		errorCode = errorCode / 16;
	}

	/*Fill the hex format with zeros. example: when storeHexValue = 500 the string length is shorter than 4char so i add a 0 in front*/
	int hexBytes = 4;
	if (storeHexValue.shortFormat.size() < hexBytes)
		for (int i = 0; i < (hexBytes - storeHexValue.shortFormat.size()); i++)
		{
			storeHexValue.shortFormat += "0";
			storeHexValue.longFormat += "0";
		}

	/*In glew.h you wil find some formats like 0x00004000*/
	storeHexValue.longFormat += "0000";

	/*I need the 0x format for glew.h -> i append x0 because it will be reversed*/
	storeHexValue.shortFormat += "x0";
	storeHexValue.longFormat += "x0";

	reverse(storeHexValue.shortFormat.begin(), storeHexValue.shortFormat.end());
	reverse(storeHexValue.longFormat.begin(), storeHexValue.longFormat.end());
	/*std::cout << "The gl error number in hexadecimal short format: " << storeHexValue.shortFormat << " long format: "
		<< storeHexValue.longFormat << std::endl;*/
}