void threadDpsArray() {
	while (true) {
		int mapId = GetCurrentMapId();
		try {
			Agent a;
			Character c;
			Float f, tmp;
			if (logDpsArray) {
				if (GetCurrentMapId() != mapId) { //clear deque on mapchange
					dpsDeque.clear();
					mapId = GetCurrentMapId();
				}
				std::sort(dpsDeque.begin(), dpsDeque.end());
				while (a.BeNext()) {
					if (a.GetType() != GW2::AGENT_CATEGORY_CHAR)
						continue;
					int id = a.GetAgentId();
					f.id = id;
					if (id == 0) // || !a.IsValid()) 
						continue;
					c = a.GetCharacter();
					if (!c.IsValid())
						continue;
					int cHealth = (int) c.GetCurrentHealth();
					int mHealth = (int) c.GetMaxHealth();
					DWORD time;
					if (cHealth == mHealth)
						time = 0;
					auto e = (lower_bound(dpsDeque.begin(), dpsDeque.end(), f));
					if (e == dpsDeque.end()) { //element doesn't exist in deque
						f.cHealth = cHealth;
						f.mHealth = mHealth;
						if (cHealth == mHealth)
							f.time = 0;
						else
							f.time = timeGetTime();
						if (f.id != 0)
							cout << "newid: " << f.id << " time: " << f.time << endl;
						dpsDeque.push_front(f);
					}
					else {
						if (e->id != id) {
							f.cHealth = cHealth;
							f.mHealth = mHealth;
							if (cHealth == mHealth)
								f.time = 0;
							else
								f.time = timeGetTime();
							if (f.id != 0)
								cout << "newid: " << f.id << " time: " << f.time << endl;
							dpsDeque.push_front(f);
						}
						if (e->time == 0 && !(cHealth == mHealth))
							e->time = timeGetTime();
						else if (cHealth == mHealth)
							e->time = 0;
						e->cHealth = cHealth; //id and mHealth don't change
						//e->mHealth = mHealth;
					}
				} //while end
			}
			// go easy on the cpu //check for interruption
			boost::this_thread::sleep_for(boost::chrono::milliseconds{200});
		}
		catch (boost::thread_interrupted&) {
			return;
		}
	}
}