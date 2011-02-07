#include "boost/utility.hpp"
#include "boost/optional.hpp"
#include "boost/shared_ptr.hpp"

#include <string>
#include <map>

#include "notification_center.h"

#include <cstdio>

void proc(const char *notify_name, void *data) {
	printf("notify_name: %s\n", notify_name);
	printf("data: %08x\n", data);
	if(data != NULL) {
		printf("data: %s\n", data);
	}
}

int main() {
	using namespace org::click3;

	boost::shared_ptr<NotificationCenter> default_center = NotificationCenter::GetDefaultCenter();
	char notify_name[256] = "hoge";
	std::string notify_name2("hoge");

	printf("empty\n");
	default_center->SendNotification("hoge", "hoge");
	default_center->SendNotification(NULL, "NULL");
	default_center->SendNotification(notify_name, "hoge_char");
	default_center->SendNotification(notify_name2.c_str(), "hoge_string");

	printf("add hoge\n");
	default_center->AddObserver("hoge", proc);

	default_center->SendNotification("hoge", "hoge");
	default_center->SendNotification(NULL, "NULL");
	default_center->SendNotification(notify_name, "hoge_char");
	default_center->SendNotification(notify_name2.c_str(), "hoge_string");

	printf("add NULL\n");
	default_center->AddObserver(NULL, proc);

	default_center->SendNotification("hoge", "hoge");
	default_center->SendNotification(NULL, "NULL");
	default_center->SendNotification(notify_name, "hoge_char");
	default_center->SendNotification(notify_name2.c_str(), "hoge_string");

	printf("remove hoge\n");
	default_center->RemoveObserver("hoge", proc);

	default_center->SendNotification("hoge", "hoge");
	default_center->SendNotification(NULL, "NULL");
	default_center->SendNotification(notify_name, "hoge_char");
	default_center->SendNotification(notify_name2.c_str(), "hoge_string");

	printf("remove NULL\n");
	default_center->RemoveObserver(NULL, proc);

	default_center->SendNotification("hoge", "hoge");
	default_center->SendNotification(NULL, "NULL");
	default_center->SendNotification(notify_name, "hoge_char");
	default_center->SendNotification(notify_name2.c_str(), "hoge_string");
	return 0;
}
