#pragma once
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <set>
#include <deque>
#include <list>
#include "glslprogram.h" //Mat4 data type
#include "Scene.h"
#include "Cube.h"

#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> tcp_connection_ptr;

	/*static pointer create(boost::asio::io_service& io_service)
	{
	return pointer(new tcp_connection(io_service));
	}*/

	tcp_connection(boost::asio::io_service& io_service,
		std::vector<tcp_connection_ptr>& clients)
		: socket_(io_service), clients_(clients)
	{
		ret_.push_back(std::make_pair("", mat4(0.0f)));
		ret_.push_back(std::make_pair("", mat4(0.0f)));
		ret_.push_back(std::make_pair("", mat4(0.0f)));
		ret_.push_back(std::make_pair("", mat4(0.0f)));
	}

	~tcp_connection()
	{
		socket_.close();
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start(int pID)
	{
		ret_.front() = std::make_pair(std::to_string(pID), mat4(0.0f));
		boost::asio::async_write(socket_,
			boost::asio::buffer(ret_, 2048*4),
			boost::bind(&tcp_connection::handle_read, this,
			boost::asio::placeholders::error));
	}

	void deliver(boost::shared_ptr<string> obj)
	{
		//std::cout << "Server send data to connection" << std::endl;
		//char carray[2048 * 2] = "";
		//for (int i = 0; i < obj.size(); ++i)
		//	carray[i] = obj[i];
		//carray[obj.size()] = '\0';
		
		std::ostream stream(&outStrm);
		stream << obj;
		
		boost::asio::async_write(socket_,
			boost::asio::buffer(*obj, 2048*4),
			boost::bind(&tcp_connection::handle_write, this,
			boost::asio::placeholders::error,
			obj));
	}

	void handle_read(const boost::system::error_code& error)
	{
		if (!error)
		{
			ripe = true;
			boost::asio::async_read(socket_,
				boost::asio::buffer(ret_, 2048*4),
				boost::bind(&tcp_connection::handle_read, shared_from_this(),
				boost::asio::placeholders::error));
		}
		// Else remove player from server
		else
		{
			//clients_.erase(shared_from_this());
		}
	}

	void handle_write(const boost::system::error_code& error, boost::shared_ptr<std::string> s)
	{
		if (!error)
		{
			//std::cout << "connection sent data to client" << std::endl;
			// all these pops might not be useful at all
		}
		// Else remove player from server
		else
		{
			//std::cout << "Error sending from connection to client:" << error << std::endl;
			//system("pause");
			//clients_.erase(shared_from_this());
			socket_.close();
		}
	}
	std::vector <pair<string, mat4>> * getState()
	{
		return &ret_;
	}

	//tell server the data is deprecated
	void age(){
		ripe = false;
	}
	bool isRipe(){
		return ripe;
	}

private:
	std::vector<tcp_connection_ptr>& clients_;
	tcp::socket socket_;
	std::vector <pair<string, mat4>> ret_;
	bool ripe;//determines if the received message is read or not
	boost::asio::streambuf outStrm;

};

typedef boost::shared_ptr<tcp_connection> tcp_connection_ptr;

class tcp_server
{
public:
	tcp_server(boost::asio::io_service& io_service,
		const tcp::endpoint& endpoint)
		: io_service_(io_service),
		acceptor_(io_service, tcp::endpoint(tcp::v4(), 13))
	{
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));

		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));
		emptyRet.push_back(std::make_pair("", mat4(3.0f)));

		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));

		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));

		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));

		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));
		retVec_.push_back(std::make_pair("", mat4(3.0f)));

		pID = 0;
		start_accept();
	}

	void start_accept()
	{
		tcp_connection_ptr new_connection(new tcp_connection(io_service_, clients_));

		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
			boost::asio::placeholders::error));
	}

	void handle_accept(tcp_connection_ptr connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout << "Client connected!" << std::endl;
			join(connection);
			connection->start(pID);
			pID++;
		}
		start_accept();
	}

	void join(tcp_connection_ptr player)
	{
		std::cout << "added client to players" << std::endl;
		clients_.push_back(player);
	}

	// If a player leaves? Probably will never be used.
	void leave(tcp_connection_ptr player)
	{
		//clients_.erase(player);
	}

	void send(std::string const& obj)
	{
		boost::shared_ptr<std::string> strP = boost::make_shared<std::string>(obj);

		if (clients_.empty())
		{
			//std::cout << "no clients to send to" << std::endl;
		}
		else
		{
			for each(tcp_connection_ptr client in clients_)
			{
				//std::cout << *strP << endl << endl;
				client->deliver(strP);
			}
		}
	}

	std::vector <pair<string, mat4>> * getState()
	{
		if (clients_.empty())
		{
			///std::cout << "getting state but no clients" << std::endl;
			return &emptyRet;
		}
		for each(tcp_connection_ptr client in clients_)
		{
			retVec_[i++] = (*client->getState())[0];
			retVec_[i++] = (*client->getState())[1];
			retVec_[i++] = (*client->getState())[2];
			retVec_[i++] = (*client->getState())[3];
		}
		i = 0;
		return &retVec_;
	}

	//tell server the data is deprecated
	void age(){
		for each(tcp_connection_ptr client in clients_)
		{
			client->age();
		}
	}

	bool isRipe(uint cliID){
		if (cliID < clients_.size())
			return clients_[cliID]->isRipe();
		else
			return false;
	}

	void getDataState(bool* state){
		for (int i = 0; i < 4; i++){
			state[i] = isRipe(i);
		}
	}

private:
	int pID;
	tcp::acceptor acceptor_;
	boost::asio::io_service& io_service_;
	std::vector <tcp_connection_ptr> clients_;
	std::vector <pair<string, mat4>> emptyRet;
	std::vector <pair<string, mat4>> retVec_;
	int i = 0;
};