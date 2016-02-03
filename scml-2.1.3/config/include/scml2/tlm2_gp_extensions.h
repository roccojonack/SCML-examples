#ifndef SCML2_TLM2_GP_EXTENSIONS_H
#define SCML2_TLM2_GP_EXTENSIONS_H

#include <tlm.h>

namespace scml2 {
  struct tlm2_gp_extensions {
    public:
      tlm2_gp_extensions(const tlm::tlm_generic_payload& payload) : payload(payload) {
      }

      template<typename T> T* get_extension() const {
        return payload.get_extension<T>();
      }

    private:
      const tlm::tlm_generic_payload& payload;
  };
}

#endif
