void threadAutoClicker() {
	while (true) {
		try {
			if (autoClick)
				DoubleClick();
			boost::this_thread::sleep_for(boost::chrono::milliseconds{10});
		}
		catch (boost::thread_interrupted&) {
			return;
		}
	}
}