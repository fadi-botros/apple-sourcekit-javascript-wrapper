#include "sourcekitd.h"
#include <node/node.h>

namespace sourcekit {
	using namespace v8;
	using v8::ReturnValue;

	void sourceKitInitialize(const FunctionCallbackInfo<Value>& args) {
		Isolate *isolate = args.GetIsolate();
		if (args.Length() != 0) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Initialize takes only one arguments")));
		}
		sourcekitd_initialize();
		args.GetReturnValue().Set(Null(isolate));
	}

	void sourceKitUninitialize(const FunctionCallbackInfo<Value>& args) {
		Isolate *isolate = args.GetIsolate();
		if (args.Length() != 0) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "UnInitialize takes only one arguments")));
		}
		sourcekitd_shutdown();
		args.GetReturnValue().Set(Null(isolate));
	}

	void addKeyToDictionary(sourcekitd_object_t dict, Local<String> &key, Local<Value> &value) {
		char *utfKey = new char[key->Utf8Length()];
		key->WriteUtf8(utfKey, key->Utf8Length());
		auto val = value->ToString();
		char *utfVal = new char[val->Utf8Length()];
		key->WriteUtf8(utfVal, val->Utf8Length());
		sourcekitd_request_dictionary_set_string(dict, sourcekitd_uid_get_from_cstr(utfKey), utfVal);
	}

	void dumpDictionary(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		sourcekitd_object_t dict = (sourcekitd_object_t) args.This()->GetAlignedPointerFromInternalField(0);
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, sourcekitd_request_description_copy(dict)));
	}

	void newConstructor(const FunctionCallbackInfo<Value>& args) {
		args.GetReturnValue().Set(Object::New(args.GetIsolate()));
	}

	void dictionaryCreate(const FunctionCallbackInfo<Value>& args) {
		Isolate *isolate = args.GetIsolate();
		if (args.Length() > 1) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Create dictionary may take only one optional argument")));
		}

		sourcekitd_object_t dict = sourcekitd_request_dictionary_create(0, 0, 0);

		auto map = (args[0]->ToObject(isolate));
		for(int i=0;i<map->GetOwnPropertyNames()->Length();i++) {
			auto key = (map->GetOwnPropertyNames()->Get(i))->ToString();
			auto value = map->Get(key);
			addKeyToDictionary(dict, key, value);
		}

		auto functionTpl = FunctionTemplate::New(isolate, newConstructor);
		functionTpl->SetClassName(String::NewFromUtf8(isolate, "SourcekitDictionary"));
		functionTpl->InstanceTemplate()->SetInternalFieldCount(1);
		NODE_SET_PROTOTYPE_METHOD(functionTpl, "dump", dumpDictionary);

		auto obj = functionTpl->InstanceTemplate()->NewInstance();
		obj->SetAlignedPointerInInternalField(0, dict);

		args.GetReturnValue().Set(obj);
	}

	void Init(Local<Object> exports) {
		NODE_SET_METHOD(exports, "init", sourceKitInitialize);
		NODE_SET_METHOD(exports, "shutdown", sourceKitUninitialize);
		NODE_SET_METHOD(exports, "dictionaryCreate", dictionaryCreate);
	}

	NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

}
