/*
 *  Copyright (c) 2019 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef TEST_SCENARIO_NETWORK_TRAFFIC_ROUTE_H_
#define TEST_SCENARIO_NETWORK_TRAFFIC_ROUTE_H_

#include <memory>
#include <vector>

#include "rtc_base/copy_on_write_buffer.h"
#include "system_wrappers/include/clock.h"
#include "test/scenario/network/network_emulation.h"

namespace webrtc {
namespace test {

// Represents the endpoint for cross traffic that is going through the network.
// It can be used to emulate unexpected network load.
class TrafficRoute {
 public:
  TrafficRoute(Clock* clock,
               EmulatedNetworkReceiverInterface* receiver,
               EmulatedEndpoint* endpoint);
  ~TrafficRoute();

  // Triggers sending of dummy packets with size |packet_size| bytes.
  void TriggerPacketBurst(size_t num_packets, size_t packet_size);
  // Sends a packet over the nodes and runs |action| when it has been delivered.
  void NetworkDelayedAction(size_t packet_size, std::function<void()> action);

  void SendPacket(size_t packet_size);

 private:
  void SendPacket(size_t packet_size, uint16_t dest_port);

  Clock* const clock_;
  EmulatedNetworkReceiverInterface* const receiver_;
  EmulatedEndpoint* const endpoint_;

  uint16_t null_receiver_port_;
  std::unique_ptr<EmulatedNetworkReceiverInterface> null_receiver_;
  std::vector<std::unique_ptr<EmulatedNetworkReceiverInterface>> actions_;
};

}  // namespace test
}  // namespace webrtc

#endif  // TEST_SCENARIO_NETWORK_TRAFFIC_ROUTE_H_
