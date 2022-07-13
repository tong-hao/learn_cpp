/* Example of using sigaction() to setup a signal handler with 3 arguments
 * including siginfo_t.
 */
#include <iostream>
#include <signal.h>
#include <string.h>
#include <unistd.h>

static void hdl(int sig, siginfo_t *siginfo, void *context) {
	std::cout << "sig: " << sig << ::strsignal(sig)
	          << ", Sending PID: " << (long)siginfo->si_pid
	          << ", UID: " << (long)siginfo->si_uid << std::endl;

	::signal(sig, SIG_DFL);
	::raise(sig);
}

int main(int argc, char *argv[]) {
	struct sigaction act;
	memset(&act, 0, sizeof(act));

	/* Use the sa_sigaction field because the handles has two additional
	 * parameters */
	act.sa_sigaction = &hdl;

	/* The SA_SIGINFO flag tells sigaction() to use the sa_sigaction field, not
	 * sa_handler. */
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);

	while (1) {
		sleep(10);
	}

	return 0;
}