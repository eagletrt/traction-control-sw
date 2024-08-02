#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>

const char *get_user_home() {
	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL) {
		homedir = getpwuid(getuid())->pw_dir;
	}
	return homedir;
}
