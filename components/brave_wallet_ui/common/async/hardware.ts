// Copyright (c) 2021 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import * as BraveWallet from 'gen/brave/components/brave_wallet/common/brave_wallet.mojom.m.js'
import { SignHardwareTransactionType } from '../hardware_operations'
import { getLocale } from '../../../common/locale'
import WalletApiProxy from '../../common/wallet_api_proxy'
import LedgerBridgeKeyring from '../../common/ledgerjs/eth_ledger_bridge_keyring'
import TrezorBridgeKeyring from '../../common/trezor/trezor_bridge_keyring'

export async function signTrezorTransaction (apiProxy: WalletApiProxy, path: string, txInfo: BraveWallet.TransactionInfo): Promise<SignHardwareTransactionType> {
  const chainId = await apiProxy.ethJsonRpcController.getChainId()
  const nonce = await apiProxy.ethTxController.getNonceForHardwareTransaction(txInfo.id)
  if (!nonce || !nonce.nonce) {
    return { success: false, error: getLocale('braveWalletApproveTransactionError') }
  }
  txInfo.txData.baseData.nonce = nonce.nonce
  const deviceKeyring = apiProxy.getKeyringsByType(BraveWallet.TREZOR_HARDWARE_VENDOR) as TrezorBridgeKeyring
  const signed = await deviceKeyring.signTransaction(path, txInfo, chainId.chainId)
  if (!signed || !signed.success || !signed.payload) {
    return { success: false, error: getLocale('braveWalletSignOnDeviceError') }
  }
  const { v, r, s } = signed.payload
  const result =
    await apiProxy.ethTxController.processHardwareSignature(txInfo.id, v, r, s)
  if (!result.status) {
    return { success: false, error: getLocale('braveWalletProcessTransactionError') }
  }
  return { success: result.status }
}

export async function signLedgerTransaction (apiProxy: WalletApiProxy, path: string, txInfo: BraveWallet.TransactionInfo): Promise<SignHardwareTransactionType> {
  const nonce = await apiProxy.ethTxController.getNonceForHardwareTransaction(txInfo.id)
  if (!nonce || !nonce.nonce) {
    return { success: false, error: getLocale('braveWalletApproveTransactionError') }
  }
  const data = await apiProxy.ethTxController.getTransactionMessageToSign(txInfo.id)
  if (!data || !data.message) {
    return { success: false, error: getLocale('braveWalletNoMessageToSignError') }
  }
  const deviceKeyring = apiProxy.getKeyringsByType(BraveWallet.LEDGER_HARDWARE_VENDOR) as LedgerBridgeKeyring
  const signed = await deviceKeyring.signTransaction(path, data.message.replace('0x', ''))
  if (!signed || !signed.success || !signed.payload) {
    const error = signed && signed.error ? signed.error : getLocale('braveWalletSignOnDeviceError')
    return { success: false, error: error }
  }
  const { v, r, s } = signed.payload
  const result = await apiProxy.ethTxController.processHardwareSignature(txInfo.id, '0x' + v, '0x' + r, '0x' + s)
  if (!result || !result.status) {
    return { success: false, error: getLocale('braveWalletProcessTransactionError') }
  }
  return { success: result.status }
}