﻿#ifndef GOTOCOMMAND_H_
#define GOTOCOMMAND_H_

#include <string>
#include <boost/algorithm/string.hpp>

#include "../CommandHandler.hpp"
#include "../Network/Protocol.hpp"
#include "../Utils/Logger.hpp"

class GotoCommand : public ICommand {
public:
	~GotoCommand() {}

	virtual void Execute(Client* sender, const CommandArgs& args)
	{
		Server* server = Server::GetInstance();
		std::string worldName = args.front();

		boost::algorithm::to_lower(worldName);

		World* world = server->GetWorld(worldName);
		if (world == nullptr) {
			ClassicProtocol::SendMessage(sender, "&cWorld &f" + worldName + "&c does not exist");
			return;
		}

		if (!world->GetActive()) {
			ClassicProtocol::SendMessage(sender, "&cWorld &f" + worldName + "&c is not loaded");
			return;
		}

		if (worldName == sender->GetWorld()->GetName()) {
			ClassicProtocol::SendMessage(sender, "&eWarp nine. Engage. &9*Woosh*");
			return;
		}

		sender->GetWorld()->RemoveClient(sender->GetPid());
		world->AddClient(sender);
		server->BroadcastMessage("&e&6" + sender->GetName() + " &ewarped to &a" + worldName);
	}

	virtual std::string GetDocString() { return "/goto <world name> - warps to world"; }
	virtual unsigned int GetArgumentAmount() { return 1; }
	virtual unsigned int GetPermissionLevel() { return 0; }

private:

};

#endif // GOTOCOMMAND_H_
