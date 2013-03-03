#include <string>
#include "../../DataUrlStream.h"

struct Example
{
	const char* dataUrl;
	const char* name;
	const char* data;

} examples[] = {
	{
		"data:audio/mpeg;base64,YW55IGNhcm5hbCBwbGVhc3VyZS4="
		"audio/mpeg"
		"any carnal pleasure."
	}
};

int main()
{
	int result = 0;
	for (int i = 0; i < sizeof(examples)/sizeof(*examples); ++i)
	{
		Example example = examples[i];
		JS::DataUrlStream stream(example.dataUrl);

		std::string name(stream.name());
		//std::cout << name << " == " << example.name << std::endl;
		result |= name != example.name;

		std::string data(stream.readBlock(stream.length()).data(), stream.length());
		//std::cout << data << " == " << example.data << std::endl;
		result |= data != example.data;
	}
	return result;
}
