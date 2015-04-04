void threadSpeedometer() {
	double pollingRate = 100; // ms
	int pId = 0;
	Vector3 pPos = Vector3(0, 0, 0);

	timer::cpu_timer timer;
	timer.stop();
	while (true) {
		try {

			if (logSpeedometer) {
				int cId = 0;
				Vector3 cPos = Vector3(0, 0, 0);

				// get data
				if (logSpeedometerEnemy) {
					if (locked.valid) {
						cId = locked.id;
						cPos = locked.pos;
					}
				}
				else {
					cId = self.id;
					cPos = self.pos;
				}

				// verify if current valid
				if (cId == 0) {
					if (!timer.is_stopped())
						timer.stop();

					if (pId != 0) {
						pId = 0;
						pPos = Vector3(0, 0, 0);

						if (!bufferSpeedometer.empty())
							bufferSpeedometer.clear();
					}

					continue;
				}

				// if current not previous, set previous and restart
				if (cId != pId) {
					if (!timer.is_stopped())
						timer.stop();

					if (!bufferSpeedometer.empty())
						bufferSpeedometer.clear();

					pId = cId;
					pPos = cPos;
					continue;
				}

				// valid, start timer if not started
				if (timer.is_stopped()) {
					timer.start();
					continue;
				}

				// all good, poll every 250ms
				timer::cpu_times elapsed = timer.elapsed();
				double elapsedMs = elapsed.wall / 1e6;
				if (elapsedMs > pollingRate) {
					timer.start();

					int dist = int(Dist(pPos, cPos));
					bufferSpeedometer.push_front(dist);

					pId = cId;
					pPos = cPos;
				}
			}
			else {
				if (!timer.is_stopped())
					timer.stop();

				if (pId != 0) {
					pId = 0;
					pPos = Vector3(0, 0, 0);
				}

				if (!bufferSpeedometer.empty())
					bufferSpeedometer.clear();

				if (!logSpeedometer)
					Sleep(100); // Thread not needed, sleep
			}

			// go easy on the cpu //check for interruption
			boost::this_thread::sleep_for(boost::chrono::milliseconds{1});
		}
		catch (boost::thread_interrupted&) {
			return;
		}
	}
}
