/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_BRAVE_WALLET_BRAVE_WALLET_SERVICE_DELEGATE_IMPL_H_
#define BRAVE_BROWSER_BRAVE_WALLET_BRAVE_WALLET_SERVICE_DELEGATE_IMPL_H_

#include <memory>
#include <string>
#include <vector>

#include "base/memory/scoped_refptr.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observation.h"
#include "base/values.h"
#include "brave/components/brave_wallet/browser/brave_wallet_service_delegate.h"
#include "brave/components/brave_wallet/common/brave_wallet.mojom.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace value_store {
class ValueStore;
}

namespace content {
class BrowserContext;
}

namespace extensions {
class Extension;
}

namespace brave_wallet {

class BraveWalletServiceDelegateImpl : public BraveWalletServiceDelegate {
 public:
  explicit BraveWalletServiceDelegateImpl(content::BrowserContext* context);
  BraveWalletServiceDelegateImpl(const BraveWalletServiceDelegateImpl&) =
      delete;
  BraveWalletServiceDelegateImpl& operator=(
      const BraveWalletServiceDelegateImpl&) = delete;
  ~BraveWalletServiceDelegateImpl() override;

  void IsCryptoWalletsInstalled(
      IsCryptoWalletsInstalledCallback callback) override;
  void IsMetaMaskInstalled(IsMetaMaskInstalledCallback callback) override;
  void ImportFromCryptoWallets(
      const std::string& password,
      const std::string& new_password,
      ImportFromCryptoWalletsCallback callback) override;
  void ImportFromMetaMask(const std::string& password,
                          const std::string& new_password,
                          ImportFromMetaMaskCallback callback) override;
  void HasEthereumPermission(const std::string& origin,
                             const std::string& account,
                             HasEthereumPermissionCallback callback) override;
  void ResetEthereumPermission(
      const std::string& origin,
      const std::string& account,
      ResetEthereumPermissionCallback callback) override;

 private:
  friend class BraveWalletServiceDelegateImplUnitTest;
  void OnCryptoWalletsLoaded(const std::string& password,
                             const std::string& new_password,
                             ImportFromCryptoWalletsCallback callback,
                             bool should_unload);

  void GetLocalStorage(const extensions::Extension* extension,
                       const std::string& password,
                       const std::string& new_password,
                       ImportFromCryptoWalletsCallback callback);
  void OnGetLocalStorage(const std::string& password,
                         const std::string& new_password,
                         ImportFromCryptoWalletsCallback callback,
                         std::unique_ptr<base::DictionaryValue> dict);

  bool IsLegacyCryptoWallets() const;
  bool IsCryptoWalletsInstalledInternal() const;
  const extensions::Extension* GetCryptoWallets();
  const extensions::Extension* GetMetaMask();

  void EnsureConnected();
  void OnConnectionError();

  mojo::Remote<brave_wallet::mojom::KeyringController> keyring_controller_;
  content::BrowserContext* context_;
  scoped_refptr<extensions::Extension> extension_;
  base::WeakPtrFactory<BraveWalletServiceDelegateImpl> weak_ptr_factory_;
};

}  // namespace brave_wallet

#endif  // BRAVE_BROWSER_BRAVE_WALLET_BRAVE_WALLET_SERVICE_DELEGATE_IMPL_H_