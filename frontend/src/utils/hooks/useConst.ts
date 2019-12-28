import {useRef} from "react";

type ConstRef<T> = { value: T };

export function useConst<T>(value: T | (() => T)) {
	const ref = useRef<ConstRef<T>>(null);

	if (ref.current == null) {
		ref.current = {
			value: typeof value === "function" ? (value as Function)() : value
		}
	}

	return ref.current.value;
}
