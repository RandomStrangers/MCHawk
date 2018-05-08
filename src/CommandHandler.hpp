﻿#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#include <string>
#include <vector>
#include <map>

#include "Client.hpp"
#include <iostream>
typedef std::vector<std::string> CommandArgs;

class Command {
public:
	Command(std::string name) : m_name(name) { }

	virtual ~Command()
	{
		for (auto& obj : m_subcommands)
			delete obj;
	}

	std::string GetName() { return m_name; }

	virtual void Execute(Client* sender, const CommandArgs& args) = 0;
	virtual std::string GetDocString() = 0;
	virtual unsigned int GetArgumentAmount() = 0;
	virtual unsigned int GetPermissionLevel() = 0;

	std::vector<Command*> GetSubcommands() { return m_subcommands; }

	void AddSubcommand(Command* command) { m_subcommands.push_back(command); }

	bool HandleSubcommands(Client* sender, const CommandArgs& args)
	{
		for (auto& obj : m_subcommands) {
			if (args[0] == obj->GetName()) {
				CommandArgs subArgs = args;

				subArgs.erase(subArgs.begin());

				obj->Execute(sender, subArgs);

				return true;
			}
		}

		return false;
	}
protected:
	std::string m_name;
private:
	std::vector<Command*> m_subcommands;
};

typedef std::map<std::string, Command*> CommandMap;
typedef std::map<std::string, std::string> AliasMap;

class CommandHandler {
public:
	CommandHandler() {}

	virtual ~CommandHandler();

	typedef std::map<std::string, Command*> CommandMap;

	Command* GetCommand(std::string name);
	const CommandMap& GetCommandList() const { return m_commands; }

	void Register(std::string name, Command* command, std::string aliases="");
	void Execute(Client* sender, std::string name, const CommandArgs& args);
	void Handle(Client* sender, std::string message);

private:
	std::map<std::string, Command*> m_commands;
	std::map<std::string, std::string> m_aliases;
};

#endif // COMMANDHANDLER_H_
