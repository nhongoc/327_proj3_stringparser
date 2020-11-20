/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <fstream>
#include <sstream>
#include <string.h>
#include "../327_proj3_test/includes/constants.h"
#include "../327_proj3_test/includes/StringParserClass.h"

using namespace std;
namespace KP_StringParserClass {

StringParserClass::StringParserClass(void) {
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

StringParserClass::~StringParserClass(void) {
	cleanup();
}

int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}
	pStartTag = new char[strlen(pStart)];
	pEndTag = new char[strlen(pEnd)];
	strcpy(pStartTag, pStart);
	strcpy(pEndTag, pEnd);
	areTagsSet = true;
	return SUCCESS;
}

int StringParserClass::getDataBetweenTags(char *pDataToSearchThru,
		std::vector<std::string> &myVector) {
	if (!areTagsSet || pStartTag == NULL || pEndTag == NULL) {
		return ERROR_TAGS_NULL;
	}
	if (pDataToSearchThru == NULL) {
		return ERROR_DATA_NULL;
	}
	myVector.clear();
	string temp = string(pDataToSearchThru);
	while (temp.find(pStartTag) != string::npos
			&& temp.find(pEndTag) != string::npos) {
		int start = temp.find(pStartTag);
		int end = temp.find(pEndTag);
		myVector.push_back(
				temp.substr(start + (int) strlen(pStartTag),
						end - start - (int) strlen(pEndTag) + 1));
		temp.erase(start, (end - start) + (int) strlen(pEndTag));
	}
	return SUCCESS;
}

void StringParserClass::cleanup() {
	if (pStartTag) {
		delete[] pStartTag;
		pStartTag = NULL;
	}
	if (pEndTag) {
		delete[] pEndTag;
		pEndTag = NULL;
	}
	areTagsSet = false;
}

int findTag(char *pTagToLookFor, char *&pStart, char *&pEnd) {
	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}
	int i = 0;
	while (pStart[i] != 0) {
		bool found = true;
		if (pStart[i] == '<') {
			for (unsigned int j = 0; j < strlen(pTagToLookFor); j++) {
				if (pEnd[i + j] != pTagToLookFor[j]) {
					found = false;
				}
			}
			if (found) {
				*pStart = pStart[i];
				*pEnd = pStart[i + strlen(pTagToLookFor)];
				return SUCCESS;
			}
		}
		i++;
	}
	return FAIL;
}
}
