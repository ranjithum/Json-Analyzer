package main

import (
	"bytes"
)

type GenericBlock interface {
	EvaluateBlock() bool
	ToString() string
	AddCodeBlocks(blk GenericBlock)
}

type listOfCodeBlocks []GenericBlock

func (lc *listOfCodeBlocks) AppendCodeBlock(blk GenericBlock) {
	*lc = append(*lc, blk)
}

func NewListOfCodeBlock() *listOfCodeBlocks {
	return &listOfCodeBlocks{}
}

func (lc *listOfCodeBlocks) ToString() string {
	var cBlock bytes.Buffer
	for _, eachBlock := range *lc {
		cBlock.WriteString(eachBlock.ToString())
	}
	return cBlock.String()
}

var global_listOfCodeBlocks listOfCodeBlocks
