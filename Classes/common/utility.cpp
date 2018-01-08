#include "utility.h"

using namespace rapidjson;
using namespace std;

USING_NS_CC;

Utility::Utility() {

}

Utility::~Utility() {

}

Document Utility::loadJson(char* fileName) {
	Document document;
	string json;

	Data fileData = FileUtils::getInstance()->getDataFromFile(fileName);
	size_t fileSize = fileData.getSize();
	unsigned char* bytes = fileData.getBytes();

	json = string((char*)bytes, 0, fileSize);

	StringStream stream = StringStream(json.c_str());

	document.ParseStream<kArrayType>(stream);

	bool error = document.HasParseError();

	if (error) {
		CCLOG("Parse error [%d - %d]", error, document.GetParseError());
		document.Parse("{\"text\":\"파일을 읽을수 없습니다.\"}");
		return document;
	}

	//issue - 파일 불러오기 실패시 예외처리(지금은 프로그램 종료됨)

	return document;
}