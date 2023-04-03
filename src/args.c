#include "include/args.h"

inline bool is_short_flag(const char *arg) {
	return (arg[0] == '-') && (arg[1] != '-') && (arg[1] != '\0');
}

inline bool is_long_flag(const char *arg) {
	return (arg[0] == '-') && (arg[1] == '-');
}

bool process_args(config *conf, int argc, const char **argv) {
	shift(argv);
	--argc;

	while (argc > 0) {
		if (is_short_flag(argv[0])) {
			bool result = process_short_flag(conf, &argc, &argv);
			if (!result)
				return false;
		} else if (is_long_flag(argv[0])) {
			bool result = process_long_flag(conf, &argc, &argv);
			if (!result)
				return false;
		} else {
			ERR_FMT("\"%s\": Unknown command.", argv[0]);
			return false;
		}
	}

	return true;
}

static void print_help(void) { printf("help\n"); }

bool process_short_flag(config *conf, int *argc, const char ***argv) {
	flag arg = FLAG_NULL;
	int consumed = 1;

	for (int i = 0; i < COUNT_FLAGS; ++i) {
		if (strcmp((*argv)[0], flags_short[i]) == 0) {
			arg = i;
			goto found;
		}
	}
	ERR_FMT("\"%s\": Unknown command.", (*argv)[0]);
	return false;

found:
	switch (arg) {
	case FLAG_HELP:
		print_help();
		exit(EXIT_SUCCESS);

	case FLAG_VERBOSE:
		conf->verbose = true;
		break;

	case FLAG_TITLE: {
		if (*argc < 2) {
			ERR_FMT("Missing argument for \"%s\" flag.", (*argv)[0]);
			return false;
		}
		if (is_long_flag((*argv)[1]) || is_short_flag((*argv)[1])) {
			ERR_FMT("Missing argument for \"%s\" flag.", (*argv)[0]);
			return false;
		}
		conf->title = (*argv)[1];
		++consumed;
	} break;

	case FLAG_AUTHOR: {
		if (*argc < 2) {
			ERR_FMT("Missing argument for \"%s\" flag.", (*argv)[0]);
			return false;
		}
		if (is_long_flag((*argv)[1]) || is_short_flag((*argv)[1])) {
			ERR_FMT("Missing argument for \"%s\" flag.", (*argv)[0]);
			return false;
		}
		conf->author = (*argv)[1];
		++consumed;
	} break;

	case FLAG_NEW_BOOK:
		conf->cmd = CMD_NEW_BOOK;
		break;

	case FLAG_LIST_BOOKS:
		conf->cmd = CMD_LIST_BOOKS;
		break;

	default:
		ERR("Fatal error.");
		return false;
	}

	for (int i = 0; i < consumed; ++i)
		shift(*argv);
	*argc -= consumed;
	return true;
}


bool process_long_flag(config *conf, int *argc, const char ***argv) {
	flag arg = FLAG_NULL;
	int consumed = 1;

	for (int i = 0; i < COUNT_FLAGS; ++i) {
		if (strcmp((*argv)[0], flags_long[i]) == 0) {
			arg = i;
			goto found;
		}
	}
	ERR_FMT("\"%s\": Unknown command.", (*argv)[0]);
	return false;

found:
	switch (arg) {
	case FLAG_HELP:
		print_help();
		exit(EXIT_SUCCESS);

	case FLAG_VERBOSE:
		conf->verbose = true;
		break;

	case FLAG_TITLE: {
		if (*argc < 2) {
			ERR_FMT("Missing argument for \"%s\" flag.", (*argv)[0]);
			return false;
		}
		if (is_long_flag((*argv)[1]) || is_short_flag((*argv)[1])) {
			ERR_FMT("Missing argument for \"%s\" flag.", (*argv)[0]);
			return false;
		}
		conf->title = (*argv)[1];
		++consumed;
	} break;

	case FLAG_AUTHOR: {
		if (*argc < 2) {
			ERR_FMT("Missing argument for \"%s\" flag.", (*argv)[0]);
			return false;
		}
		if (is_long_flag((*argv)[1]) || is_short_flag((*argv)[1])) {
			ERR_FMT("Missing argument for \"%s\" flag.", (*argv)[0]);
			return false;
		}
		conf->author = (*argv)[1];
		++consumed;
	} break;

	case FLAG_NEW_BOOK:
		conf->cmd = CMD_NEW_BOOK;
		break;

	case FLAG_LIST_BOOKS:
		conf->cmd = CMD_LIST_BOOKS;
		break;

	default:
		ERR("Fatal error.");
		return false;
	}

	for (int i = 0; i < consumed; ++i)
		shift(*argv);
	*argc -= consumed;
	return true;
}
