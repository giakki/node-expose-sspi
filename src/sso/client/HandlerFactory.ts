import { AbstractHandler } from './AbstractHandler';
import { BasicHandler } from './BasicHandler';
import { DigestHandler } from './DigestHandler';
import { NegotiateHandler } from './NegotiateHandler';

export class HandlerFactory {
  static instantiate(authenticationType: string): AbstractHandler | null {
    if (authenticationType === 'Negotiate') {
      return new NegotiateHandler();
    }
    if (authenticationType === 'NTLM') {
      return new NegotiateHandler('NTLM');
    }
    if (authenticationType === 'Basic') {
      return new BasicHandler();
    }
    if (authenticationType === 'Digest') {
      return new DigestHandler();
    }
    return null;
  }
}
