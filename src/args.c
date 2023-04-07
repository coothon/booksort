#include "include/args.h"

inline bool is_long_flag(const char *arg) {
	return (arg[0] == '-') && (arg[1] == '-');
}

bool process_args(config *conf, int argc, const char **argv) {
	shift(argv);
	--argc;

	while (argc > 0) {
		if (is_long_flag(argv[0])) {
			bool result = process_long_flag(conf, &argc, &argv);
			if (!result)
				return false;
		} else {
			error_put("\"%s\": Unknown command.", argv[0]);
			return false;
		}
	}

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
	error_put("\"%s\": Unknown command.", (*argv)[0]);
	return false;

found:
	switch (arg) {
	case FLAG_HELP:
		put_help();
		exit(EXIT_SUCCESS);

	case FLAG_VERBOSE:
		conf->verbose = true;
		break;

	case FLAG_TITLE: {
		if (*argc < 2) {
			error_put("Missing argument for \"%s\" flag.", (*argv)[0]);
			put_usage();
			return false;
		}
		if (is_long_flag((*argv)[1])) {
			error_put("Missing argument for \"%s\" flag.", (*argv)[0]);
			put_usage();
			return false;
		}
		conf->title = (*argv)[1];
		++consumed;
	} break;

	case FLAG_AUTHOR: {
		if (*argc < 2) {
			error_put("Missing argument for \"%s\" flag.", (*argv)[0]);
			put_usage();
			return false;
		}
		if (is_long_flag((*argv)[1])) {
			error_put("Missing argument for \"%s\" flag.", (*argv)[0]);
			put_usage();
			return false;
		}

		conf->author = (*argv)[1];
		++consumed;
	} break;

	case FLAG_GENRE: {
		if (*argc < 2) {
			error_put("Missing argument for \"%s\" flag.", (*argv)[0]);
			put_usage();
			return false;
		}
		if (is_long_flag((*argv)[1])) {
			error_put("Missing argument for \"%s\" flag.", (*argv)[0]);
			put_usage();
			return false;
		}

		conf->genre = (*argv)[1];
		++consumed;
	} break;

	case FLAG_NEW_BOOK:
		conf->cmd = CMD_NEW_BOOK;
		break;

	case FLAG_REMOVE_BOOK:
		conf->cmd = CMD_REMOVE_BOOK;
		break;

	case FLAG_LIST_BOOKS:
		conf->cmd = CMD_LIST_BOOKS;
		break;

	default:
		error_put("Fatal error.");
		return false;
	}

	for (int i = 0; i < consumed; ++i)
		shift(*argv);
	*argc -= consumed;
	return true;
}
