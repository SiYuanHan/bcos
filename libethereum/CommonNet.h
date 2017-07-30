/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file CommonNet.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 *
 * Miscellanea required for the PeerServer/Session classes.
 */

#pragma once

#include <string>
#include <chrono>
#include <libdevcore/Common.h>


namespace dev
{

class OverlayDB;

namespace eth
{

#if ETH_DEBUG
static const unsigned c_maxHeaders = 2048;		///< Maximum number of hashes BlockHashes will ever send.
static const unsigned c_maxHeadersAsk = 2048;	///< Maximum number of hashes GetBlockHashes will ever ask for.
static const unsigned c_maxBlocks = 128;		///< Maximum number of blocks Blocks will ever send.
static const unsigned c_maxBlocksAsk = 128;		///< Maximum number of blocks we ask to receive in Blocks (when using GetChain).
static const unsigned c_maxPayload = 262144;	///< Maximum size of packet for us to send.
#else
static const unsigned c_maxHeaders = 2048;		///< Maximum number of hashes BlockHashes will ever send.
static const unsigned c_maxHeadersAsk = 2048;	///< Maximum number of hashes GetBlockHashes will ever ask for.
static const unsigned c_maxBlocks = 128;		///< Maximum number of blocks Blocks will ever send.
static const unsigned c_maxBlocksAsk = 128;		///< Maximum number of blocks we ask to receive in Blocks (when using GetChain).
static const unsigned c_maxPayload = 262144;	///< Maximum size of packet for us to send.
#endif
static const unsigned c_maxNodes = c_maxBlocks; ///< Maximum number of nodes will ever send.
static const unsigned c_maxReceipts = c_maxBlocks; ///< Maximum number of receipts will ever send.

class BlockChain;
class TransactionQueue;
class EthereumHost;
class EthereumPeer;

enum SubprotocolPacketType : byte
{
	StatusPacket = 0x00,
	NewBlockHashesPacket = 0x01,
	TransactionsPacket = 0x02,
	GetBlockHeadersPacket = 0x03,
	BlockHeadersPacket = 0x04,
	GetBlockBodiesPacket = 0x05,
	BlockBodiesPacket = 0x06,
	NewBlockPacket = 0x07,

	GetNodeDataPacket = 0x0d,
	NodeDataPacket = 0x0e,
	GetReceiptsPacket = 0x0f,
	ReceiptsPacket = 0x10,

	//同步配置
	NodeInfoSync = 0x11,			//增加节点信息
	DelNodeInfoSync = 0x12,			//删除节点信息

	PacketCount
};

enum class Asking
{
	State,
	BlockHeaders,
	BlockBodies,
	NodeData,
	Receipts,
	Nothing
};

enum class SyncState
{
	NotSynced,			///< Initial chain sync has not started yet
	Idle,				///< Initial chain sync complete. Waiting for new packets
	Waiting,			///< Block downloading paused. Waiting for block queue to process blocks and free space
	Blocks,				///< Downloading blocks
	State,				///< Downloading state
	NewBlocks,			///< Downloading blocks learned from NewHashes packet

	Size		/// Must be kept last
};

struct SyncStatus
{
	SyncState state = SyncState::Idle;
	unsigned protocolVersion = 0;
	unsigned startBlockNumber;
	unsigned currentBlockNumber;
	unsigned highestBlockNumber;
	bool majorSyncing = false;
};

}
}