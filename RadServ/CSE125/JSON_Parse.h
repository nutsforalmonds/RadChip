#ifndef JSON_PARSE_H
#define	JSON_PARSE_H

#include "rapidjson/document.h"
#include "rapidjson/filestream.h"
#include <stdio.h>
#include <iostream>


class JSON_Parser
{
public:
	JSON_Parser(const char* FileName){
		fopen_s(&pFile, FileName, "r");
		rapidjson::FileStream is(pFile);
		document.ParseStream<0>(is);
		if (document.IsObject()){
			printf("Parsing Map file: %s\n", FileName);
		}
		else{
			printf("ERROR Parsing Map File: %s\n", FileName);
		}
		fclose(pFile);
	}

	string GetMapName(){
		return document["map_name"].GetString();
	}


	//SHADERS
	int GetShaderCount(){
		return document["num_shaders"].GetInt();
	}

	string GetShaderName(int i){
		rapidjson::Value& shaders = document["shaders"];
		return shaders[(uint)i]["name"].GetString();
	}

	string GetShaderVert(int i){
		rapidjson::Value& shaders = document["shaders"];
		return shaders[(uint)i]["vert"].GetString();
	}

	string GetShaderFrag(int i){
		rapidjson::Value& shaders = document["shaders"];
		return shaders[(uint)i]["frag"].GetString();
	}


	//AUDIO
	int GetAudioCount(){
		return document["num_audio"].GetInt();
	}

	string GetAudioName(int i){
		rapidjson::Value& audio = document["audio"];
		return audio[(uint)i]["name"].GetString();
	}

	string GetAudioPath(int i){
		rapidjson::Value& audio = document["audio"];
		return audio[(uint)i]["path"].GetString();
	}



	//TEXTURE
	int GetTextureCount(){
		return document["num_texture"].GetInt();
	}

	string GetTextureName(int i){
		rapidjson::Value& texture = document["texture"];
		return texture[(uint)i]["name"].GetString();
	}

	string GetTexturePath(int i){
		rapidjson::Value& texture = document["texture"];
		return texture[(uint)i]["path"].GetString();
	}

	string GetTextureType(int i){
		rapidjson::Value& texture = document["texture"];
		return texture[(uint)i]["type"].GetString();
	}

	string GetTextureExt(int i){
		rapidjson::Value& texture = document["texture"];
		return texture[(uint)i]["ext"].GetString();
	}

	bool GetTextureCube(int i){
		rapidjson::Value& texture = document["texture"];
		if (texture[(uint)i]["cube"].GetInt()){
			return true;
		}
		else{
			return false;
		}
	}



private:
	FILE *pFile;
	rapidjson::Document document;
	
};

#endif	/* JSON_PARSE_H */