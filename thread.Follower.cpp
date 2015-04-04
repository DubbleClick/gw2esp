void threadFollower() {

	while (true) {
		try {

			if (follow) {
				if (!followAgent.IsValid())
					followAgent = GetLockedSelection();
				else
					if (followAgent.GetPos().x != 0 && followAgent.GetPos().y != 0) {
						if (MoveToPos(followAgent.GetPos()) == 0) {//arrived
							ReleaseButton('w');
							ReleaseButton('a');
							ReleaseButton('d');
							follow = false;
							//followAgent = {};
							ZeroMemory(&followAgent, sizeof(Agent));
						}
					}
					else
						followAgent = GetLockedSelection();
			}

			else {
				//followAgent = {};
				ZeroMemory(&followAgent, sizeof(Agent));
			}

			//check for interrupt
			boost::this_thread::sleep_for(boost::chrono::milliseconds{50});
		}
		catch (boost::thread_interrupted&) {
			return;
		}
	}
}