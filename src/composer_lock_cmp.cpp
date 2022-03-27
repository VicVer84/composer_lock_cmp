#include "composer_lock_cmp.h"

using namespace std;
using json = nlohmann::json;


pkgByTypes ReadPackages(std::string&& filename, std::vector<std::string> types) {
	pkgByTypes pkg;
	std::vector<std::string> v{"dist", "source"};
	std::ifstream ifs(filename);

	if (!ifs) {
		return pkg;
	}

	json j = json::parse(ifs);
	for (std::string type : types) {
		if (j.find(type) != j.end()) {
			for (auto& el : j[type].items()) {
				for (std::string s : v) {
					for (auto& pkg_dist : el.value()[s].items()) {
						if (pkg_dist.key().find("reference") != std::string::npos) {
							std::string name = el.value()["name"].get<std::string>();
							std::string reference = pkg_dist.value().get<std::string>();
							pkg[type][name][s] = reference;
						}
					}
				}
			}
		}
	}
	return pkg;
}

void Print(const pkgByTypes& pkg) {
	for (auto& type : pkg) {
		std::cout << type.first << std::endl;
		for (auto& name : type.second) {
			std::cout << "  " << name.first << std::endl;
			for (auto& ref : name.second) {
				std::cout << "    " << ref.first << " : " << ref.second << std::endl;
			}
		}
	}
}

void Compare(pkgByTypes& first, pkgByTypes& second) {
	for (auto& type : first) {
		for (auto& name : type.second) {
			for (auto& s : name.second) {
				if (second[type.first][name.first][s.first] != s.second) {
					std::cout << "  " << type.first << " : " << name.first << " : " << s.first << "\n";
					std::cout << "    " << s.second << " != " << second[type.first][name.first][s.first] << '\n';
				}
			}
		}
	}
}


int main() {	
	std::vector<std::string> v{ "packages", "packages-dev" };

	pkgByTypes pkg_master = ReadPackages("z:\\Visual Studio\\Mos.ru\\composer_lock_cmp\\bin\\Debug\\composer.lock", v);
	pkgByTypes pkg_MR = ReadPackages("z:\\Visual Studio\\Mos.ru\\composer_lock_cmp\\bin\\Debug\\composer (1).lock", v);

	Compare(pkg_master, pkg_MR);
	
	return 0;	
}