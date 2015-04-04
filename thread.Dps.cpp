void threadDps() {
	int pAgentId = 0;
	int pHealth = 0;
	double pollingRate = 250; // ms

	timer::cpu_timer timer;
	while (true) {
		try {

			if (logDps && locked.valid && locked.id == pAgentId) {
				if (timer.is_stopped()) {
					timer.start();
					//bufferDps.push_front(0);
					pHealth = locked.cHealth;
					continue;
				}

				timer::cpu_times elapsed = timer.elapsed();
				double elapsedMs = elapsed.wall / 1e6;
				if (elapsedMs > pollingRate) {
					timer.start();
					int cHealth = locked.cHealth;

					if (pHealth == 0)
						pHealth = cHealth;

					int dmg = pHealth - cHealth;
					pHealth = cHealth;

					if (!dpsAllowNegative && dmg < 0)
						dmg = 0;

					if (locked.cHealth != 0)
						bufferDps.push_front(dmg);

					int avg = 0;
					int bs = bufferDps.size();
					for (int i = 0; i < bs; i++) {
						avg += bufferDps[i];
					}
					if (avg == 0)
						bufferDps.clear();

					if (locked.valid)
						if (locked.cHealth == locked.mHealth)
							bufferDps.clear();
				}
			}
			else {
				if (!timer.is_stopped()) {
					timer.stop();
					pHealth = 0;
				}

				if (!bufferDps.empty())
					bufferDps.clear();

				if (locked.valid && locked.id != pAgentId)
					pAgentId = locked.id;

				if (!logDps)
					Sleep(100); // Thread not needed, sleep
			}

			// go easy on the cpu //check for interrupt
			boost::this_thread::sleep_for(boost::chrono::milliseconds{1});
		}
		catch (boost::thread_interrupted&) {
			return;
		}
	}
	
}
