#ifndef _ACC_CALC_HPP_
#define _ACC_CALC_HPP_

/*
  Module : Accumulator calculator IP + AXI DMA

  Description : The IP communicates with the DRAM memory in the PS
  through the AXI DMA, receiving non black pixels from a picture
  with extracted edges, and sending to the DRAM the calculated
  circle coordinates around the pixel for the given radius
*/

#include <tlm>
#include <tlm_utils/simple_target_socket.h>
#include <tlm_utils/simple_initiator_socket.h>

//ADDRESS SPACE OFFSET FOR REGISTERS
const sc_dt::sc_uint<64> MM2S_DMACR_OFFSET  = 0;
const sc_dt::sc_uint<64> MM2S_DMASR_OFFSET  = 4;  //04 hex
const sc_dt::sc_uint<64> MM2S_SA_OFFSET     = 24; //18 hex
const sc_dt::sc_uint<64> MM2S_LENGTH_OFFSET = 40; //28 hex
const sc_dt::sc_uint<64> S2MM_DMACR_OFFSET  = 48; //30 hex
const sc_dt::sc_uint<64> S2MM_DMASR_OFFSET  = 52; //34 hex
const sc_dt::sc_uint<64> S2MM_DA_OFFSET     = 72; //48 hex
const sc_dt::sc_uint<64> S2MM_LENGTH_OFFSET = 88; //58 hex
//ADDRESS SPACE OFFSET LIST END

class acc_calc : public sc_core::sc_module {
public:
  //Constructor
  acc_calc(sc_core::sc_module_name);

  //Target socket for register configuration
  tlm_utils::simple_target_socket<acc_calc> reg_conf_tsoc;

  //Initiator socket for direct memory access
  tlm_utils::simple_initiator_socket<acc_calc> dma_isoc;

protected:
  //REGISTER LIST
  //Memory Mapped to Stream registers
  //MM2S DMA control register
  sc_dt::sc_uint<32> mm2s_dmacr;
  //MM2S DMA status register
  sc_dt::sc_uint<32> mm2s_dmasr;
  //MM2S source address register (lower 32bits)
  sc_dt::sc_uint<32> mm2s_sa;
  //MM2S length register (num. of bytes to transfer)
  sc_dt::sc_uint<32> mm2s_length;


  //Stream to Memory Mapped registers
  //S2MM DMA control register
  sc_dt::sc_uint<32> s2mm_dmacr;
  //S2MM DMA status register
  sc_dt::sc_uint<32> s2mm_dmasr;
  //S2MM destination address register (lower 32bits)
  sc_dt::sc_uint<32> s2mm_da;
  //S2MM length register (num. of bytes to transfer)
  sc_dt::sc_uint<32> s2mm_length;
  //REGISTER LIST END

  typedef tlm::tlm_base_protocol_types::tlm_payload_type pl_t;

  //blocking transport method for the register conf. socket
  void b_transport_reg(pl_t&, sc_core::sc_time&);

  //
}

#endif
