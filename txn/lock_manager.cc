
// Lock manager implementing deterministic two-phase locking as described in
// 'The Case for Determinism in Database Systems'.

#include "txn/lock_manager.h"


deque<LockManagerA::LockRequest>* LockManagerA::getLockQueue(const Key& key){
  deque<LockRequest> *dq = lock_table_[key];
  if(!dq){
    dq = new deque<LockRequest>();
    lock_table_[key] = dq;
  }
  return dq;
}

LockManagerA::LockManagerA(deque<Txn*>* ready_txns) {
  ready_txns_ = ready_txns;
}

bool LockManagerA::WriteLock(Txn* txn, const Key& key) {
  //
  // Implement this method!
  return true;
}

bool LockManagerA::ReadLock(Txn* txn, const Key& key) {
  return WriteLock(txn, key);
}

void LockManagerA::Release(Txn* txn, const Key& key) {
  deque<LockRequest> *queue = getLockQueue(key);
  bool owner = true;

  for(auto iterator = queue->begin();iterator<queue->end();iterator++){
    if(iterator->txn_ == txn){
      queue->erase(iterator);
      break;
    }
    owner = false;
  }
  if(!queue->empty() && owner){
    LockRequest next = queue->front();
    if(--txn_waits_[next.txn_]){
      ready_txns_ -> push_back(next.txn_);
      txn_waits_.erase(next.txn_);
    }
  }
}

LockMode LockManagerA::Status(const Key& key, vector<Txn*>* owners) {
  //
  // Implement this method!
  return UNLOCKED;
}