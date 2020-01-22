#include "misc.h"

namespace myAddon {

std::map<std::string, Credentials> credMap;

Napi::Value e_AcquireCredentialsHandle(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    throw Napi::Error::New(
        env, "AcquireCredentialsHandle: Wrong number of arguments.");
  }

  std::u16string packageName = info[0].As<Napi::String>();
  Credentials c;

  SECURITY_STATUS secStatus =
      AcquireCredentialsHandle(NULL, (LPWSTR)packageName.c_str(), SECPKG_CRED_BOTH, NULL,
                               NULL, NULL, NULL, &c.credHandle, &c.expiry);
  if (secStatus != SEC_E_OK) {
    throw Napi::Error::New(env, "Cannot FreeContextBuffer: secStatus = " +
                                    std::to_string(secStatus));
  }
  
  std::string key = c.serialize();
  credMap[key] = c;

  return JS::convert(env, &c);
}

}  // namespace myAddon
